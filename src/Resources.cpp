#include "Resources.h"

Resources::Resources()
{
	loadTextures();
	loadBuffers();
	loadBackground();
	m_font.loadFromFile("font.ttf");
	setPauseScreen();
	for (int i = 0; i < 5; i++)
	{
		m_animation[i] = Animation(m_textures[i],sf::Vector2u(3, 4), 1);
	}
	
}

//=======================================================================================
Resources::~Resources(){}

//======================================================================================

void Resources::setAnimation(int i ,sf::Time deltaTime, sf::Sprite& player , int dir)
{
	m_animation[i].update(dir, deltaTime);
	player.setTextureRect(m_animation[i].uvRect);
}

//=======================================================================================
Resources& Resources::instance()
{
	static Resources inst;
	return inst;
}

//=======================================================================================
void Resources::setPauseScreen()
{
	m_pauseWindow.setFillColor(sf::Color(179, 218, 255, 255));
	m_pauseWindow.setPosition(sf::Vector2f(600, 250));
	m_pauseWindow.setSize(sf::Vector2f(340, 230));
	m_pauseWindow.setOutlineThickness(3);
	m_pauseWindow.setOutlineColor(sf::Color::Black);
	auto buttonSize = sf::Vector2f(30, 30);
	auto buttonPos = sf::Vector2f(550, 450);

	m_pauseText.setFont(m_font);
	m_pauseText.setString("Pause");
	m_pauseText.Bold;
	m_pauseText.setOutlineColor(sf::Color(12, 36, 97, 255));
	m_pauseText.setOutlineThickness(3);
	m_pauseText.setCharacterSize(80);
	m_pauseText.setColor(sf::Color(29, 209, 161, 255));
	m_pauseText.setPosition(sf::Vector2f(660, 260));
	SetButtons();
}

//=======================================================================================
void Resources::SetButtons()
{
	for (int i = 0; i < MENU_BUTTONS ; i++)
	{
		m_pauseButtons[i].setTexture(&m_pauseTextures[i]);
		m_pauseButtons[i].setSize(sf::Vector2f(90, 90));
		m_pauseButtons[i].setPosition(sf::Vector2f(620 + i * 100, 380));
	}
	m_pauseButtons[Music].setOutlineThickness(4);
	m_pauseButtons[Music].setOutlineColor(sf::Color::Green);
}

//=======================================================================================
void Resources::loadTextures()
{
	for (int i = 0; i < NUM_OF_PICS; i++)
		for (int j = 0; j< DIRECTIONS ; j++)
			m_textures[i][j].loadFromFile(objectTextures[i][j]);

	for (int i = 0; i < MENU_BUTTONS; i++)
		m_pauseTextures[i].loadFromFile(buttonTextures[i]);
}

//=======================================================================================
sf::Texture* Resources::getTexture(char c)
{
	switch (c)
	{
	case 'K': return &m_textures[load_King][0];
	case 'M': return &m_textures[load_Mage][0];
	case 'W': return &m_textures[load_Warrior][0];
	case 'T': return &m_textures[load_Thief][0];
	case 'X': return &m_textures[load_Teleport][0];
	case 'F': return &m_textures[load_Key][0];
	case '=': return &m_textures[load_Wall][0];
	case '@': return &m_textures[load_Throne][0];
	case '#': return &m_textures[load_Gate][0];
	case '!': return &m_textures[load_Orge][0];
	case '*': return &m_textures[load_Fire][0];
	case '^': return &m_textures[load_Gnome][0];
	case '%': return &m_textures[load_Gift][0];
	}
}

//=======================================================================================
sf::Texture* Resources::getTexture(int index , int dir)
{
	return &m_textures[index][dir];
}

//=======================================================================================
sf::Texture* Resources::getTexture(int index) 
{
	return &m_textures[index][0];
}

//=======================================================================================
sf::Texture* Resources::getBackground(int index)
{
	return &m_bg[index];
}

//=======================================================================================
sf::RectangleShape* Resources::getPauseButtons(int index)
{
	return &m_pauseButtons[index];
}

//=======================================================================================
void Resources::loadBackground()
{
	auto loadPic = sf::Texture();
	loadPic.loadFromFile("gamebg.png");
	m_bg.push_back(loadPic);

	loadPic.loadFromFile("help.png");
	m_bg.push_back(loadPic);

	loadPic.loadFromFile("bg.png");
	m_bg.push_back(loadPic);
}

//=======================================================================================
void Resources::loadBuffers()
{
	for (int i = 0; i < NUM_OF_SOUNDS; i++)
	{
		if(!m_buffers[i].loadFromFile(soundBuffers[i]))
			return;
		m_sounds[i].setBuffer(m_buffers[i]);
		m_sounds[i].setVolume(20);
	}
	m_music.openFromFile("bgMusic2.wav");
	m_music.setLoop(true);
	m_music.setVolume(20);
}

//=======================================================================================
void Resources::playSound(int index) 
{
	m_sounds[index].play();
}

//=======================================================================================
void Resources::setVolume()
{
	static bool music_on = true;
	int volume = 20;

	if (music_on)
	{
		volume = 0;
		music_on = false;
		m_pauseButtons[Music].setOutlineColor(sf::Color::Red);
	}
	else
	{
		m_pauseButtons[Music].setOutlineColor(sf::Color::Green);
		music_on = true;
	}

	for (int i = 0; i < NUM_OF_SOUNDS; i++)
	{
		m_sounds[i].setVolume(volume);
	}
	m_music.setVolume(volume);
}

//=======================================================================================
void Resources::drawPauseScreen(sf::RenderWindow& window)
{
	window.draw(m_pauseWindow);
	window.draw(m_pauseText);
	for (int i = 0; i < 3; i++)
	{
		window.draw(m_pauseButtons[i]);
	}	
}

//=======================================================================================
sf::Font* Resources::getFont()
{
	return &m_font;
}

//=======================================================================================
void Resources::playMusic()
{
	static bool musicOn = false; // check if the music is played.
	if (!musicOn)
	{
		m_music.play();
		musicOn = true;
		return;
	}
	m_music.pause();
	musicOn = false;
}