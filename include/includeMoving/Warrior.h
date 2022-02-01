#pragma once

#include "includeMoving/MovingObject.h"


class Warrior : public MovingObject
{
public:
	using MovingObject::MovingObject;
	virtual void handleCollision(GameObject& gameObject) override;
	virtual void animateDirection(int dir, sf::Time deltaTime) override;

protected:
	
};