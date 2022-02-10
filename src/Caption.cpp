#include "Caption.h"

Caption::Caption() : m_level(0), m_stageTime(0) , m_lives(0)
{
	setText(m_stageTimeText, 0);
	setText(m_levelText, 1);
	setText(m_livesLeft, 2);
	m_livesLeft.setString("Lives left: ");
	m_hearts.loadFromFile("heart.png");
	setButtons();
}
//=======================================================================================

void Caption::setText(sf::Text& text , int i)
{
	text.setFont(*Resources::instance().getFont());
	text.setCharacterSize(40);
	text.setPosition( 300 * i + 50 , WINDOW_HEIGHT - BAR_SIZE + 10);
	text.setColor(sf::Color::Green);
	text.setOutlineColor(sf::Color::Blue);
	text.setOutlineThickness(3);
}

//=======================================================================================
Caption::~Caption() {}

void Caption::updateTime(float time)
{

	m_stageTime += time;
	m_stageTime -= m_timer.getElapsedTime().asSeconds();
	
	m_stageTimeText.setString("Time left: " + std::to_string((int)m_stageTime));

	m_timer.restart();
}

//=======================================================================================
void Caption::updateLevel()
{
	m_level++;
	m_levelText.setString("Level:" + std::to_string(m_level));
	m_timer.restart();

}

//=======================================================================================

void Caption::updateLives(int number)
{
	m_lives += number;
}
//=======================================================================================
int Caption::getLives() const
{
	return m_lives;
}

//=======================================================================================
float Caption::getTime() const
{
	return m_stageTime;
}

//=======================================================================================
void Caption::resetTime()
{
	m_stageTime = 0;
}

//=======================================================================================
void Caption::draw(sf::RenderWindow& window)
{
	updateTime(0);
	window.draw(m_levelText);
	window.draw(m_stageTimeText);
	window.draw(m_livesLeft);
	auto sprite = sf::Sprite();
	sprite.setTexture(m_hearts);
	for (int i = 0; i < m_lives; i++)
	{
		sprite.setPosition(sf::Vector2f(170 + m_livesLeft.getPosition().x + 60 * i, m_livesLeft.getPosition().y));
		window.draw(sprite);
	}
}

//=======================================================================================
void Caption::printMessege(const sf::String text, sf::RenderWindow& window)
{
	//set the message settings
	auto message = sf::Text(text, *Resources::instance().getFont());
	message.Bold;
	message.setOutlineColor(sf::Color(12, 36, 97, 255));
	message.setOutlineThickness(3);
	message.setCharacterSize(70);
	message.setColor(sf::Color(29, 209, 161, 255));
	message.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2.5));
	message.setOrigin(sf::Vector2f(message.getGlobalBounds().width / 2, message.getGlobalBounds().height / 2));
	
	// print the background
	sf::Sprite bg;
	bg.setTexture(*Resources::instance().getBackground(0));
	window.draw(bg);
	window.draw(message);
	window.display();
	auto event = sf::Event{};

	while (window.waitEvent(event)) // wait until Space is pressed
	{
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)
			|| (event.type == sf::Event::Closed))
			return;
	}
}

//=======================================================================================
int Caption::HandleClick(const sf::Vector2f location)
{
	static bool music_on= true;
	for (int i = 0; i < MENU_BUTTONS; i++)
	{
		if (m_pauseButtons[i].handleClick(location))
		{
			if (i == Music)
			{
				Resources::instance().setVolume();
				m_pauseButtons[Music].setHover(music_on);
				music_on = !music_on;
			}
			return i;
		}
	}
}

//==============================================================================================
void Caption::setButtons()
{
	for (int i = 0; i < MENU_BUTTONS; i++)
		m_pauseButtons[i] = Button(sf::Vector2f(90, 90), i, sf::Vector2f(660 + i * 100, 390));
}

//=========================================================================================
void Caption::drawButtons(sf::RenderWindow& window)
{
	for (int i = 0; i < MENU_BUTTONS; i++)
	{
		m_pauseButtons[i].draw(window);
	}
}