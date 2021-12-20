#pragma once
#include "Location.h"
#include "MovingObject.h"

class King : public MovingObject
{
public:
	King(int startR, int startC, sf::Vector2f throne);
	King(sf::Vector2f loc, sf::Vector2f throne);
	bool isVictory();					// check if king set on throne

private:

	sf::Vector2f m_throne;		// location of throne
	char m_lastTile;
};