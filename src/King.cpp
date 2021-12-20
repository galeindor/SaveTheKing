#include "King.h"

King::King(int startR, int startC, sf::Vector2f throne)
		:m_throne(throne), m_lastTile(' ') , MovingObject(startR, startC)
{}

King::King(sf::Vector2f loc, sf::Vector2f throne)
	: MovingObject(loc), m_throne(throne), m_lastTile(' ')
{}


bool King::isVictory()
{
	if(m_loc.row == m_throne.row && m_loc.col == m_throne.col)
		return true;
	return false;
}