#pragma once
#include "Location.h"
#include "MovingObject.h"

class Warrior: public MovingObject
{
public:
	//Warrior(int startR, int startC);
	Warrior(Location loc);
	Location getLocation() const;	// get location of the warrior
	void setLocation(int newRow, int newCol);	// set new location for the warrior

private:
	Location m_loc;		// location member
};