
#include "includeStatic/Wall.h"

void Wall::handleCollision(King& gameObject) { m_dispatched = CollisionStatus::Not_Valid; }
void Wall::handleCollision(Thief& gameObject) { m_dispatched = CollisionStatus::Not_Valid; }
void Wall::handleCollision(Mage& gameObject) { m_dispatched = CollisionStatus::Not_Valid; }
void Wall::handleCollision(Warrior& gameObject) { m_dispatched = CollisionStatus::Not_Valid; }
void Wall::handleCollision(Gnome& gameObject) { m_dispatched = CollisionStatus::Not_Valid; }