#include "includeMoving/Mage.h"

void Mage::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this)
		return;

	gameObject.handleCollision(*this);
}

//=======================================================================================
void Mage::animateDirection(int dir , sf::Time deltaTime)
{
	Resources::instance().setAnimation(load_Mage, deltaTime, m_sprite, dir);
}