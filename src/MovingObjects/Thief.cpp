#include "includeMoving/Thief.h"

void Thief::setKey(bool status)
{
	m_key = status;
}

//=======================================================================================
bool Thief::getKey() const
{
	return m_key;
}

//=======================================================================================
void Thief::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this)
		return;

	gameObject.handleCollision(*this);
}

//=======================================================================================
void Thief::handleCollision(Gate& gameObject)
{
	m_key = false;
	m_sprite.setTexture(*Resources::instance().getTexture(load_Thief));
}

//=======================================================================================
void Thief::handleCollision(Key& gameObject)
{
	m_key = true;
	m_sprite.setTexture(*Resources::instance().getTexture(load_ThiefKey));
}

//=======================================================================================
void Thief::animateDirection(int dir , sf::Time deltaTime)
{
	
	int index;
	if (!m_key)
		index = load_Thief;
	else
		index = load_ThiefKey;
	
	Resources::instance().setAnimation(index, deltaTime, m_sprite, dir);
}