#include "includeStatic/Fire.h"

void Fire::handleCollision(Mage& gameObject)
{
	m_dispatched = CollisionStatus::Destroy;
	Resources::instance().playSound(fire_sound);
}

void Fire::handleCollision(King& gameObject) 
{
	m_dispatched = CollisionStatus::Not_Valid;
}

void Fire::handleCollision(Thief& gameObject) 
{
	m_dispatched = CollisionStatus::Not_Valid; 
}

void Fire::handleCollision(Warrior& gameObject) 
{ 
	m_dispatched = CollisionStatus::Not_Valid; 
}

void Fire::handleCollision(Gnome& gameObject) 
{
	m_dispatched = CollisionStatus::Not_Valid; 
}

