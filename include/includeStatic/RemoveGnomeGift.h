#pragma once
#include "includeStatic/Gift.h"

class RemoveGnomeGift : public Gift
{
public:
	using Gift::Gift;
	using Gift::handleCollision;
	
protected:
	void setType() override; // set type of gift
};
