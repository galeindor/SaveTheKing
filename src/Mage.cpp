#include "Mage.h"

Mage::Mage(int startR, int startC)
	:m_loc(startR, startC)
{}

Mage::Mage(Location loc)
	: m_loc(loc)
{}

void Mage::setLocation(int newRow, int newCol)
{
	m_loc.row = newRow;
	m_loc.col = newCol;
}

Location Mage::getLocation() const
{
	return m_loc;
}