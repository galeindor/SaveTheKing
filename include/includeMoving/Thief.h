#pragma once

#include "includeMoving/MovingObject.h"

class Thief : public MovingObject
{
public:
	using MovingObject::MovingObject;
	virtual void handleCollision(GameObject& gameObject) override;

	bool getKey() const;
	void setKey(bool status);

	virtual void handleCollision(Gate& gameObject) override;
	virtual void handleCollision(Key& gameObject) override;
	
protected:

	virtual void animateDirection(int dir , sf::Time deltaTime) override;
	bool m_key = false;
};