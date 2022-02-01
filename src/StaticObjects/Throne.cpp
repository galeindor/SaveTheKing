#include "includeStatic/Throne.h"

void Throne::handleCollision(King& player){ m_dispatched = CollisionStatus::Won;}
void Throne::handleCollision(Thief& ) { m_dispatched = CollisionStatus::Not_Valid; }
void Throne::handleCollision(Mage& ) { m_dispatched = CollisionStatus::Not_Valid; }
void Throne::handleCollision(Warrior& ) { m_dispatched = CollisionStatus::Not_Valid; }
void Throne::handleCollision(Gnome& ) { m_dispatched = CollisionStatus::Not_Valid; }
