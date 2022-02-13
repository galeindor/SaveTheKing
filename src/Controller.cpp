#include "Controller.h"

Controller::Controller()
    :m_board(), m_currChar(0) , m_caption(), m_numOfGnomes(0)
{}

//=======================================================================================
void Controller::run(sf::RenderWindow& window)
{
    //Resources::instance().playSound(start_sound); 
    m_board = Board(WINDOW_WIDTH, WINDOW_HEIGHT - BAR_SIZE, sf::Vector2f(0, 0));
    m_board.loadNextLevel(m_character, m_tiles);
    findGnome();
    readTeleports();

    sf::Event event;
    const sf::Time timerLimit = sf::seconds(0.1f);
    sf::Clock clock;
    sf::Time deltaTimePlayer, deltaTimeGnomes;

    m_caption.updateLevel();
    m_caption.updateTime(STAGE_TIME);
    m_caption.updateLives(3);

    bool played_countdown = false; 

    Resources::instance().playMusic();

    while (window.isOpen()) 
    {
        window.clear();
        m_board.resizeObjects(m_character, m_tiles);
        m_board.setHalo(m_character[m_currChar]);
        m_board.draw(window, m_character, m_tiles);
        m_caption.draw(window);
        window.display();

        if (m_caption.getTime() <= 4 && !played_countdown)
        { //when timer in on the last 5 seconds , a coundown sound is played
            Resources::instance().playSound(countdown_sound);
            played_countdown = true;
        }

        if (m_caption.getTime() <= 0) // time <= 0 means game over
        {
            m_caption.printMessege(" Sorry , you lost :( \n Press space Key to restart", window);
            restartLvl();
            m_caption.updateLives(-1);
        }

        if (m_caption.getLives() == 0) // end game on 0 lifes
            return;
        
        if(!eventsHandler(event,window , deltaTimePlayer))
            return;

        if (clock.getElapsedTime() >= timerLimit)
            clock.restart();
        
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            movementManger(m_currChar, deltaTimePlayer, clock);
            break;
        }

        for (int i = 0; i < m_gnomes.size(); i++) // move gnomes
        {
            if(!movementManger(m_gnomes[i], deltaTimeGnomes, m_clocks[i]))
                m_character[m_gnomes[i]]->setDirection(sf::Keyboard::Up);
        }
        // gnomes change direction only when they collide with an object , the next direction is random.
        
        if (m_won)
        {
            handleVictory(window);
            if (!m_board.loadNextLevel(m_character, m_tiles)) // if player won the last level
            {
                m_caption.printMessege(" yay,YOU WON :) \n Press space Key to continue", window);
                return;
            }
            m_caption.printMessege(" Level cleard, Good Job!!! \n Press space Key to continue", window);
            findGnome();
            readTeleports();

            // make sure the current player isnt a gnome
            while (m_character[m_currChar] == nullptr || typeid(*m_character[m_currChar]) == typeid(Gnome))
                switchCharacter();
        }
    }
}

//=======================================================================================
// this func will handle the keyboard and mouse events and return if exit button was pressed
bool Controller::eventsHandler(sf::Event& event , sf::RenderWindow& window , sf::Time& deltaTime)
{
    static int dir = 0;
    while (window.pollEvent(event))
    {
        if ((event.type == sf::Event::Closed) ||
            ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
        {
            if (!PauseMenu(window)) // if 'exit' was pressed
                return false;

            // restart the clocks of the gnomes so they wont move after the game was paused
            for (int i = 0; i < m_numOfGnomes; i++)
                m_clocks[i].restart();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            {
                dir = Down;
                m_character[m_currChar]->animateDirection(dir, sf::Time());
                switchCharacter();
                while (m_character[m_currChar] == nullptr || typeid(*m_character[m_currChar]) == typeid(Gnome))
                    switchCharacter();
            }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                m_character[m_currChar]->setDirection(sf::Keyboard::Right);
                dir = Right;
                break;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                m_character[m_currChar]->setDirection(sf::Keyboard::Down);
                dir = Down;
                break;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                m_character[m_currChar]->setDirection(sf::Keyboard::Left);
                dir = Left;
                break;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                m_character[m_currChar]->setDirection(sf::Keyboard::Up);
                dir = Up;
                break;
            }
        }
        
    }
    m_character[m_currChar]->animateDirection(dir, deltaTime);
    return true;
}

//=======================================================================================

void Controller::handleVictory(sf::RenderWindow& window)
{
    clearLastLevel();
    window.clear();
    m_won = false;
    m_caption.updateLevel();
    m_caption.resetTime();
    m_caption.updateTime(STAGE_TIME);
}

//=======================================================================================
bool Controller::movementManger(int currChar, sf::Time& deltaTime, sf::Clock& clock)
{
    m_character[currChar]->setLastLoc(); // set last location as current location
    deltaTime = clock.restart();
    m_character[currChar]->movePlayer(deltaTime);

    if (!manageCollisions(currChar,false)) // check if any collision has accured with this character and handle it
    {
        m_character[currChar]->setLocation(m_character[currChar]->getLastLoc()); // return to last 'safe' tile
        return false;
    }
    return true;
}

//=======================================================================================
void Controller::switchCharacter()
{
    m_currChar = ++m_currChar % (PLAYABLE + m_numOfGnomes); 
}

//=======================================================================================
void Controller::findGnome()
{
    for (int i = 0; i < m_character.size(); i++)
    {
        if (typeid(*m_character[i]) == typeid(Gnome))
        {
            m_gnomes.push_back(i);
            m_clocks.push_back(sf::Clock());
            m_character[i]->setDirection(sf::Keyboard::Up);
        }
    }
    m_numOfGnomes = m_gnomes.size();
}

//=======================================================================================
bool Controller::manageCollisions(int currChar , bool teleported)
{
    if (!locationAllowed(*m_character[currChar]))
        return false;

    for (auto& character : m_character)
    {
        if (character != nullptr && m_character[currChar]->checkCollision(*character))
            return false;

    }
    for (auto& tile : m_tiles) // check collisions with tiles
    {
        if (tile != nullptr && m_character[currChar]->checkCollision(*tile))
        {
                m_character[currChar]->handleCollision(*tile);
                switch (tile->getDispatch())
            {
                case CollisionStatus::Not_Valid:
                    return false;

                case CollisionStatus::Won:
                    Resources::instance().playSound(victory_sound);
                    m_won = true;
                    break;

                case CollisionStatus::Ogre:
                    Resources::instance().playSound(ogre_sound);
                    m_tiles.push_back(std::make_unique<Key>(tile->getLocation(), *Resources::instance().getTexture('F')));
                    [[fallthrough]];

                case CollisionStatus::Destroy:
                    eraseObject(*tile);
                    break;

                case CollisionStatus::Teleport:
                    if (!teleported)
                    {
                        m_character[currChar]->setLastLoc();
                        m_character[currChar]->setLocation(locateTeleport(*tile));
                        if (!manageCollisions(currChar, true))
                           return false;
                        m_character[currChar]->teleported();
                    }
                    if (!m_character[currChar]->isTp())
                    {
                       m_character[currChar]->teleported();
                       return true;                      
                    }
                    return false;
                    break;

                case CollisionStatus::Gift:
                    manageGifts(*tile);
                    eraseObject(*tile);
                    break;
            }
        }
    }
    if (m_character[currChar]->isTp())
    {
        m_character[currChar]->teleported();
    //    for (int i = 0; i < m_teleportort.size(); i++)
    //        m_teleportort[i].m_isUsed = false;
    }
    return true;
}

//=======================================================================================
bool Controller::locationAllowed(const MovingObject& shape)
{
    auto temp = shape.getSprite().getGlobalBounds();
    if (temp.width + temp.left > WINDOW_WIDTH || temp.left < 0 ||
        temp.height + temp.top > WINDOW_HEIGHT - BAR_SIZE || temp.top < 0)
        return false;

    return true;
}

//=======================================================================================
sf::Vector2f Controller::locateTeleport(const StaticObject& teleport)
{
    // every teleport built in a vector, the friend of a teleport is hes neighbor in the vecotr,
    // if the position of a teleport in the array is odd hes friend in  index -1
    // if the index is even hes friend in index +1
    for (int i = 0; i < m_teleport.size(); ++i)
    {
        if (teleport.getLocation() == m_teleport[i])
        {
            //if (m_teleportort[i].m_isUsed)
            //    break;

            // teleports are stored in a vector and linked by a following (odd,even) index couples ,
            //  for exmaple : m_teleportort[0] and m_teleportort[1] are linked.
            if (i % 2 == 0) 
            {
                //m_teleportort[i].m_isUsed = true;
                //m_teleportort[++i].m_isUsed = true;
                //return m_teleportort[i].m_loc;
                return m_teleport[++i];
            }  
            else
            {
                //m_teleportort[i].m_isUsed = true;
                //m_teleportort[--i].m_isUsed = true;
                //return m_teleportort[i].m_loc;
                return m_teleport[--i];
            }
        }
    }
    return sf::Vector2f(0,0);
}

//=======================================================================================
void Controller::readTeleports()
{
    for (auto& tile : m_tiles)
    {
        if (typeid(*tile) == typeid(Teleport))
            m_teleport.push_back(tile->getLocation());
    }
}

//=======================================================================================
void Controller::clearLastLevel()
{
    m_character.clear();
    m_tiles.clear();
    m_gnomes.clear();
    m_teleport.clear();
}

//=======================================================================================
void Controller::manageGifts(StaticObject& tile)
{
    Gift* giftPtr = dynamic_cast<Gift*> (&tile);
    switch(giftPtr->getType())
    {
    case GiftTypes::RemGnomes:
        eraseGnomes();
        break;

    case GiftTypes::TimeAdd:
        m_caption.updateTime(20);
        break;

    case GiftTypes::TimeDec:
        m_caption.updateTime(-20);
        break;
    }
}

//=======================================================================================
void Controller::eraseObject(StaticObject& staticObj)
{
    auto staticPtr = m_tiles.begin();
    for (; staticPtr != m_tiles.end(); staticPtr++)
    {
        if ((*staticPtr)->getLocation() == staticObj.getLocation())
        {
            m_tiles.erase(staticPtr);
            break;
        }
    }
}

//=======================================================================================
void Controller::eraseGnomes()
{
    Resources::instance().playSound(gnome_sound);
    for (int i = 0; i < m_gnomes.size(); i++)
        m_character[m_gnomes[i]].release();
   
    m_gnomes.clear();
}

//=======================================================================================
bool Controller::PauseMenu(sf::RenderWindow& window)
{
    sf::Clock clock;
    clock.restart();

    while (window.isOpen())
    {
        Resources::instance().drawPauseScreen(window);
        m_caption.drawButtons(window);
        window.display();
        if (auto event = sf::Event{}; window.waitEvent(event))
        {
            if ((event.type == sf::Event::Closed) ||
                ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
            {
                m_caption.updateTime(clock.getElapsedTime().asSeconds());
                return true;
            }
            
            switch (event.type)
            {
                
            case sf::Event::MouseButtonReleased:
                auto location = window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });

               if(event.mouseButton.button == sf::Mouse::Button::Left)
               {
                   auto buttonClicked = m_caption.HandleClick(location);

                   if (buttonClicked == Home)
                   {
                       Resources::instance().playMusic();
                       return false;
                   }

                   else if (buttonClicked == Restart)
                   {
                       window.clear();
                       restartLvl();
                       m_caption.updateLives(-1);
                       return true;
                   }
                   else if (buttonClicked != Music)
                   {
                       m_caption.updateTime(clock.getElapsedTime().asSeconds());
                       return true;
                   }
               }
            }
        }
    }
    m_caption.updateTime(clock.getElapsedTime().asSeconds());
    return true;
}

//=======================================================================================
void Controller::restartLvl()
{
    clearLastLevel();
    m_caption.resetTime();
    m_caption.updateTime(STAGE_TIME);
    m_board.RestartLevel(m_character, m_tiles);
    readTeleports();
    findGnome();
}