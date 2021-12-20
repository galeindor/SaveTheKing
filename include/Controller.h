#pragma once

#include "Board.h";
#include <cstdlib>
#include <conio.h>
#include <iostream>
#include "King.h"
#include "Mage.h"
#include "Warrior.h"
#include "Thief.h"
#include "Location.h"

using std::cout;

enum Keys
{
    KB_Escape = 27,
    SpecialKey = 224,
};

enum SpecialKeys
{
    KB_Up = 72,
    KB_Down = 80,
    KB_Left = 75,
    KB_Right = 77,
};

class Controller
{
public:
	Controller(std::string fileName);
    // run the game
    void run();

private:
    // check if regular key is pressed (from ASCII table)
    bool handleRegularKey(int c);

    // check if special key is pressed (e.g arrow up key)
    void handleSpecialKey();

    // get location of one of the characters
    Location getPlayerLocation(char player);

    // set location of one of the characters
    char setPlayerLocation(char player, Location loc);

    // switch between characters
    void switchPlayer();

    // calculate the new location of a character based on its move and tile stepped on
    Location calcNewLocation(char player, Location loc, int rowToAdd, int colToAdd);
    
    // check is the tile that the charcter tries to step onto is valid
    bool isValidTile(char player, char newTile);

    Board m_board;
    char m_player;

    King m_king;
    Mage m_mage;
    Warrior m_warrior;
    Thief m_thief;
};