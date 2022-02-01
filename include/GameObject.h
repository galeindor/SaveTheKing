#pragma once

#include "macros.h"
#include "Resources.h"

class King;
class Mage;
class Thief;
class Warrior;
class Gnome;
class Wall;
class Key;
class Throne;
class Fire;
class Teleport;
class Gate;
class Ogre;


class GameObject
{
public:
	GameObject(sf::Vector2f loc, const sf::Texture& texture); 

	// check if this object is colliding with the other object
	bool checkCollision(const GameObject& other);

	// virtual abstract functions of the different collisions
	virtual void handleCollision(GameObject& ) = 0;
	virtual void handleCollision(Wall& ) = 0;
	virtual void handleCollision(Throne& ) = 0;
	virtual void handleCollision(Gate& ) = 0;
	virtual void handleCollision(Fire& ) = 0;
	virtual void handleCollision(Key& ) = 0;
	virtual void handleCollision(Ogre& ) = 0;
	virtual void handleCollision(Teleport& ) = 0;
	virtual void handleCollision(King& ) = 0;
	virtual void handleCollision(Thief& ) = 0;
	virtual void handleCollision(Mage& ) = 0;
	virtual void handleCollision(Warrior& ) = 0;
	virtual void handleCollision(Gnome& ) = 0;

	// commom functions and actions of all objects
	void draw(sf::RenderWindow& window);
	sf::Vector2f getLocation() const;
	sf::Sprite getSprite() const;
	void setSpriteTexture(sf::Texture s) ;
	void setSpriteScale(double ScaleX, double ScaleY);
	virtual ~GameObject() = default; // virtual distractor

protected:
	sf::Vector2f m_location; // location of the object
	sf::Sprite m_sprite; // image of the object
};