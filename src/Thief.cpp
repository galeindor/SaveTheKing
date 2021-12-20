#include "Thief.h"

Thief::Thief(int startR, int startC)
	:m_loc(startR, startC)
{}

/*Thief::Thief(Location loc)
	: m_loc(loc)
{}
*/

void Thief::setLocation(int newRow, int newCol)
{
	m_loc.row = newRow;
	m_loc.col = newCol;
}

Location Thief::getLocation() const
{
	return m_loc;
}