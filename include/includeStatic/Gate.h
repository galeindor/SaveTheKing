#pragma once

#include "includeStatic/StaticObject.h"
#include "includeMoving/Thief.h"

class Gate : public StaticObject
{
public:
	using StaticObject::StaticObject;
	virtual void handleCollision(GameObject& gameObject) override {};
	virtual void handleCollision(Mage& gameObject) override;
	virtual void handleCollision(King& gameObject) override;
	virtual void handleCollision(Thief& gameObject) override;
	virtual void handleCollision(Warrior& gameObject) override;
	virtual void handleCollision(Gnome& gameObject) override;

private:
};