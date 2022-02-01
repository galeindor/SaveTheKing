#include "includeMoving/Gnome.h"

Gnome::Gnome(sf::Vector2f loc, const sf::Texture& texture)
	:MovingObject(loc, texture)
{
	m_speedPerSecond = m_sprite.getScale().x * 250; 
	// gnomes need to be faster than normal players
	srand(time(NULL));
}

//=======================================================================================
void Gnome::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this)
		return;

	gameObject.handleCollision(*this);
}

//=======================================================================================
void Gnome::setDirection(sf::Keyboard::Key key)
{
	setRandomDirection(); // gnome directions set randomly 
}

//=======================================================================================
void Gnome::setRandomDirection()
{
	int direction = rand() % 4;
	switch (direction)
	{
	case 0:
		m_direction = sf::Vector2f(0, -1); break;
	case 1:
		m_direction = sf::Vector2f(-1, 0); break;
	case 2:
		m_direction = sf::Vector2f(0, 1); break;
	case 3:
		m_direction = sf::Vector2f(1, 0); break;
	}
}