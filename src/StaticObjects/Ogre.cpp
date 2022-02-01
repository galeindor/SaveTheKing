#include "includeStatic/Ogre.h"
#include "includeStatic/Key.h"

void Ogre::handleCollision(Warrior& gameObject)
{
	m_dispatched = CollisionStatus::Ogre;
}

void Ogre::handleCollision(King& gameObject) { m_dispatched = CollisionStatus::Not_Valid; }
void Ogre::handleCollision(Thief& gameObject) { m_dispatched = CollisionStatus::Not_Valid; }
void Ogre::handleCollision(Mage& gameObject) { m_dispatched = CollisionStatus::Not_Valid; }
void Ogre::handleCollision(Gnome& gameObject) { m_dispatched = CollisionStatus::Not_Valid; }