#include "Menu.h"

Menu::Menu()
	: m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Save The King")
{
    for (int i = 0; i < MENU_BUTTONS ; i++) // Create the menu buttons
        m_buttons[i] = Button(sf::Vector2f(150, 150), m_texts[i], sf::Vector2f(700, 330 + i * 170)); 

    m_gameOn = m_need_help = false;

    //initiate help bar
    m_help_bar = sf::RectangleShape(sf::Vector2f(1280, 720));
    m_help_bar.setPosition(sf::Vector2f(200, 50));
    m_help_bar.setOutlineThickness(3);
    m_help_bar.setOutlineColor(sf::Color::Black);
    m_help_bar.setTexture(Resources::instance().getBackground(1)); 

    m_bg = sf::Sprite(*Resources::instance().getBackground(2));

    // set window icon 
    auto icon = sf::Image{};
    icon.loadFromFile("throne.png");
    m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

//=======================================================================================
void Menu::run()
{
    bool need_help = false;
    while (m_window.isOpen())
    {
        if(m_gameOn)
            game();
        m_window.clear();
        m_window.draw(m_bg);
        draw();
        if (m_need_help)
            m_window.draw(m_help_bar);
        m_window.display();
        eventsHandler();
    }
}

//=======================================================================================
void Menu::eventsHandler()
{
    for (auto event = sf::Event{}; m_window.pollEvent(event);)
    {
        if ((event.type == sf::Event::Closed) ||
            ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
            m_window.close();

        switch (event.type)
        {
        case sf::Event::MouseMoved: 
        {
            auto loc = m_window.mapPixelToCoords(
                { event.mouseMove.x, event.mouseMove.y });
            handleHover(loc); 
            break;
        }

        case sf::Event::MouseButtonPressed:

            auto location = m_window.mapPixelToCoords(
                { event.mouseButton.x, event.mouseButton.y });
            
            switch (event.mouseButton.button)
            {
                case sf::Mouse::Button::Left:
                    if(!m_need_help)
                        handleButtons(location); //check if a button is pressed
                    else
                        m_need_help = false; // lower the help bar if the mouse clicked anywhere
                    break;
            }
            break;
        }
    }
}

//=======================================================================================
void Menu::game()
{
    Controller().run(m_window);
    m_gameOn = false;  // once we exit the game we set the gameOn to be false
}

//=======================================================================================
void Menu::draw()
{
    for (int i = 0; i < MENU_BUTTONS; i++)
        m_buttons[i].draw(m_window);
}

//=======================================================================================
void Menu::handleButtons(const sf::Vector2f& location)
{
    for (int i = 0; i < MENU_BUTTONS; i++)
    {
        if (m_buttons[i].handleClick(location)) 
        {  
            switch (i+3)
            {
            case StartGame:
                m_gameOn = true; 
                break;

            case Help:
                m_need_help = true;
                break;

            case Exit:
                m_window.close();
                break;
            default:
                break;
            }
        }
    }
}

//=======================================================================================
void Menu::handleHover(const sf::Vector2f& location)
{
    m_buttons[m_lastHover].setHover(false); // return to default color
    for (int i = 0; i < MENU_BUTTONS; i++)
    {
        if (m_buttons[i].getGlobalBounds().contains(location))
        {
            // change the color if hovered over the button
            m_buttons[i].setHover(true);

            m_lastHover = i; // set current button as the last button hovered over
        }
    }
}