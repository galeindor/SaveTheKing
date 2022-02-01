#pragma once

#include "includeMoving/MovingObject.h"
#include <stdlib.h> 
#include <time.h> 

class Gnome : public MovingObject
{
public:
	Gnome(sf::Vector2f loc, const sf::Texture& texture);
	void setDirection(sf::Keyboard::Key key) override;
	virtual void handleCollision(GameObject& gameObject) override;

private:
	void setRandomDirection();
};