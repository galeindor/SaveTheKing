#include "includeMoving/Warrior.h"

void Warrior::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this)
		return;

	gameObject.handleCollision(*this);
}

void Warrior::animateDirection(int dir, sf::Time deltaTime)
{
	Resources::instance().setAnimation(load_Warrior, deltaTime, m_sprite, dir);
}