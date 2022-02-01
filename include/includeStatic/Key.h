#pragma once

#include "includeStatic/StaticObject.h"
#include "includeMoving/Thief.h"

class Key : public StaticObject
{
public:
	using StaticObject::StaticObject;
	virtual void handleCollision(GameObject& ) override {};
	virtual void handleCollision(Mage& ) override;
	virtual void handleCollision(King& ) override;
	virtual void handleCollision(Thief& ) override;
	virtual void handleCollision(Warrior& ) override;
	virtual void handleCollision(Gnome& ) override;

private:
};