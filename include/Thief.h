#pragma once
#include "Location.h"
#include "MovingObject.h"

class Thief: public MovingObject 
{
public:
	Thief(int startR, int startC);
	//Thief(Location loc);
	Location getLocation() const;		// get location of thief
	void setLocation(int newRow, int newCol);	// set new location for thief
private:
	Location m_loc;
};