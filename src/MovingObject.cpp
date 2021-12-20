#include "MovingObject.h"

MovingObject::MovingObject(const sf::Vector2f& loc)
	:m_location(loc)
{}

MovingObject::MovingObject(int startR, int startC)
	: m_location(startR,startC)
{}

void MovingObject::move(sf::Time deltaTime )
{
	const auto speedPerSecond = 10.f;
	m_sprite.move(m_direction * speedPerSecond * deltaTime.asSeconds());
}

void MovingObject::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

sf::Vector2f MovingObject::getLocation() const
{
	return m_location;
}

void MovingObject::setLocation(const sf::Vector2f& loc)
{
	m_location = loc;
}

void MovingObject::setDirection(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Key::Space:
		m_direction = sf::Vector2f(0, 0); break;
	case sf::Keyboard::Key::Left:
		m_direction = sf::Vector2f(-1, 0); break;
	case sf::Keyboard::Key::Down:
		m_direction = sf::Vector2f(0, 1); break;
	}
}

