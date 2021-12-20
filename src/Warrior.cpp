#include "Warrior.h"

//Warrior::Warrior(int startR, int startC)
//	:m_loc(startR, startC)
//{}

Warrior::Warrior(Location loc)
	: m_loc(loc)
{}

void Warrior::setLocation(int newRow, int newCol)
{
	m_loc.row = newRow;
	m_loc.col = newCol;
}

Location Warrior::getLocation() const
{
	return m_loc;
}