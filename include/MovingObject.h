#pragma once
#include <SFML/Graphics.hpp>

class MovingObject
{
public:
	MovingObject(const sf::Vector2f& loc);
	MovingObject(int startR, int startC);

	void move(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);
	void setLocation(const sf::Vector2f& loc);
	sf::Vector2f getLocation() const;
	void setDirection(sf::Keyboard::Key key);

protected:
	sf::Vector2f m_direction;
	sf::Vector2f m_location;
	sf::Sprite m_sprite;
};