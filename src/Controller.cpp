#include "Controller.h"

int stepCounter;
bool key, won;

Controller::Controller(std::string fileName)
    :m_board(fileName), m_player('K'),
    m_king(King(m_board.getLocation('K'), m_board.getLocation('@'))),
    m_mage(Mage(m_board.getLocation('M'))),
    m_warrior(Warrior(m_board.getLocation('W'))),
    m_thief(Thief(m_board.getLocation('T')))
{
    won = key = false;
    stepCounter = 0;
}

void Controller::run()
{
    m_board.printStats(m_player, stepCounter, key);
    m_board.print();
    for (auto exit = false; !exit; )
    {
        if (won)
        {
            m_board.clear();
            cout << "!!!!!VICTORY!!!!!\n";
            return;
        }
        auto c = _getch();
        switch (c)
        {
        case 0:
        case SpecialKey:
            handleSpecialKey();
            break;
        default:
            exit = handleRegularKey(c);
            break;
        }
        m_board.printStats(m_player, stepCounter, key);
        m_board.print();
    }
}

void Controller::handleSpecialKey()
{
    
    auto c = _getch();
    Location playerLoc = getPlayerLocation(m_player),
        newLoc;
    char newTile = ' ';
    switch (c)
    {
    case KB_Up:
        newLoc = calcNewLocation(m_player, playerLoc, -1, 0);
        break;
    case KB_Down:
        newLoc = calcNewLocation(m_player, playerLoc, 1, 0);
        break;
    case KB_Left:
        newLoc = calcNewLocation(m_player, playerLoc, 0, -1);
        break;
    case KB_Right:
        newLoc = calcNewLocation(m_player, playerLoc, 0, 1);
        break;
    default:
        break;
    }
    newTile = setPlayerLocation(m_player, newLoc);
    m_board.updateBoard(playerLoc, getPlayerLocation(m_player), m_player, newTile);
}

bool Controller::handleRegularKey(int c)
{
    switch (c)
    {
    case 'P':
    case 'p':
        switchPlayer();
        break;
    case KB_Escape:
        exit(EXIT_SUCCESS);
        return true;
    default:
        break;
    }

    return false;
}

Location Controller::getPlayerLocation(char player)
{
    switch (player)
    {
    case 'K':
        return m_king.getLocation();
    case 'M':
        return m_mage.getLocation();
    case 'W':
        return m_warrior.getLocation();
    case 'T':
        return m_thief.getLocation();
    default:
        break;
    }
}

char Controller::setPlayerLocation(char player, Location loc)
{
    char newTile = m_board.getTile(loc.row, loc.col);
    if (!isValidTile(player, newTile))
        return newTile;
    switch (player)
    {
    case 'K':
        m_king.setLocation(loc.row, loc.col);
        if (m_king.isVictory())
            won = true;
        break;
    case 'M':
        m_mage.setLocation(loc.row, loc.col);
        break;
    case 'W':
        m_warrior.setLocation(loc.row, loc.col);
        // drop the key
        if (newTile == '!')
            return newTile = 'F';
        break;
    case 'T':
        // key collected
        if (newTile == 'F')
        {
            if (key)
                return newTile;
            key = true;
        }
        // gate open if key is possesed
        if (newTile == '#')
        {
            if (!key)
                return newTile;
            key = false;
        }
        m_thief.setLocation(loc.row, loc.col);
        break;
    default:
        break;
    }
    stepCounter++;
    if (newTile == 'F' && player != 'T')
        return newTile;

    newTile = ' ';
    return newTile;
}

void Controller::switchPlayer()
{
    if (m_player == 'K')
        m_player = 'M';
    else if (m_player == 'M')
        m_player = 'W';
    else if(m_player == 'W')
        m_player = 'T';
    else
        m_player = 'K';
}

Location Controller::calcNewLocation(char player, Location loc, int rowToAdd, int colToAdd)
{
    // check if move is in the borders of the board
    if (loc.row + rowToAdd < 0 || loc.col + colToAdd < 0 ||
        loc.row + rowToAdd >= m_board.getRowSize() || loc.col + colToAdd >= m_board.getColSize())
        return loc;
    
    // check if the player tries to go through a wall
    if (m_board.getTile(loc.row, loc.col) == '=')
        return loc;
    
    // cehck if steppes on teleport, find the teleoprt to go into, forbid if mage 
    if (m_board.getTile(loc.row + rowToAdd, loc.col + colToAdd) == 'X' && player != 'M')
    {
        Location tmp = m_board.locateTeleport(Location(loc.row + rowToAdd, loc.col + colToAdd));
        if (m_board.getTile(tmp.row, tmp.col) == 'X')
            return tmp;
    }
    // move was valid, return the new location
    return Location(loc.row + rowToAdd, loc.col + colToAdd);
}

bool Controller::isValidTile(char player, char newTile)
{
    if (newTile == ' ' || newTile == 'X' || newTile == 'F')
        return true;
    switch(newTile)
    {
    case '*':
        if (player == 'M')
            return true; break;
    case '!':
        if (player == 'W')
            return true; break;
    case '#':
        if (player == 'T')
            return true; break;
    case '@':
        if (player == 'K')
            return true; break;
    }
    return false;
}