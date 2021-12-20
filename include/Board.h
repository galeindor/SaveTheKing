#pragma once
#include <vector>
#include <string>
#include "io.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::vector;

class Board
{
public:
	Board(std::string fileName);
	// clear the board
	void clear() const;
	// print the board
	void print() const;
	// update the board based on movments
	void updateBoard(Location oldLoc, Location newLoc, char player, char tile);
	// get location on the board of a character
	Location getLocation(char player);
	// get the row size of the board
	int getRowSize() const;
	// get the collumn size of the board
	int getColSize() const;
	// print info about the level
	void printStats(char currPlayer, int steps, bool key) const;
	// get the tile in a location
	char getTile(int row, int col) const;
	// find the teleport friend of a teleport stepped on
	Location locateTeleport(Location teleportLoc);

private:
	// compare between two locations are the same
	bool cmpLocations(Location one, Location two);
	// print the teleport vector onto the board
	void printTeleports();
	// stores the board of the level
	vector<vector<char>> m_matrix;
	// stores the teleports on board
	vector<Location> m_teleport;
};