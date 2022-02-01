#include "includeMoving/King.h"

void King::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this)
		return;
	
	gameObject.handleCollision(*this);
}

//=======================================================================================

void King::animateDirection(int dir, sf::Time deltaTime)
{
	Resources::instance().setAnimation(load_King,deltaTime, m_sprite, dir);
}
