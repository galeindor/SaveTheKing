#pragma once
#include "Location.h"
#include "MovingObject.h"

class Mage : public MovingObject
{
public:
	Mage(int startR, int startC);
	Mage(Location loc);
	Location getLocation() const;		// get location of the mage
	void setLocation(int newRow, int newCol);	// set new location for mage

private:
	Location m_loc;
};