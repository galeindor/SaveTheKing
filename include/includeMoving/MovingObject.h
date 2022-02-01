#pragma once
#include "GameObject.h"

class MovingObject : public GameObject
{
public:
	
	MovingObject(sf::Vector2f loc, const sf::Texture& texture);

	void movePlayer(sf::Time deltaTime);
	void setLocation(const sf::Vector2f& loc);
	virtual void setDirection(sf::Keyboard::Key key);
	
	// handle collisions with all diffrent tiles and players
	virtual void handleCollision(GameObject& ) override {};
	virtual void handleCollision(Wall& ) override {};
	virtual void handleCollision(Throne& ) override {};
	virtual void handleCollision(Gate& ) override {};
	virtual void handleCollision(Fire& ) override {};
	virtual void handleCollision(Key& ) override {};
	virtual void handleCollision(Ogre& ) override {};
	virtual void handleCollision(Teleport& ) override {};
	virtual void handleCollision(King& ) override {};
	virtual void handleCollision(Thief& ) override {};
	virtual void handleCollision(Mage& ) override {};
	virtual void handleCollision(Warrior& ) override {};
	virtual void handleCollision(Gnome& ) override {};
	
	// set & get the last location of the obj , used to return when a invalid movement is done
	void setLastLoc();
	sf::Vector2f getLastLoc() const;

	void teleported(); // switch the OnTp member.
	bool isTp(); // check if player is on teleport tile
	virtual ~MovingObject() = default;

	virtual void animateDirection(int dir, sf::Time deltaTime) {};

protected:

	// change the sprite by the direction
	

	sf::Vector2f m_direction; // movement direction
	sf::Vector2f m_lastLoc; // last location before the last movement
	bool m_onTP = false; // if player is on teleport
	float m_speedPerSecond; 

};