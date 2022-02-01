#include "includeStatic/Gate.h"

void Gate::handleCollision(Thief& player)
{
	if(!player.getKey())
		m_dispatched = CollisionStatus::Not_Valid;
	else
	{
		player.handleCollision(*this);
		Resources::instance().playSound(gate_sound);
		m_dispatched = CollisionStatus::Destroy;
	} 
}

void Gate::handleCollision(King& gameObject) { m_dispatched = CollisionStatus::Not_Valid; }
void Gate::handleCollision(Mage& gameObject) { m_dispatched = CollisionStatus::Not_Valid; }
void Gate::handleCollision(Warrior& gameObject) { m_dispatched = CollisionStatus::Not_Valid; }
void Gate::handleCollision(Gnome& gameObject) 
{ 
	m_dispatched = CollisionStatus::Not_Valid; 
}