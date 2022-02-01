#pragma once

#include "includeStatic/StaticObject.h"

enum class GiftTypes{TimeAdd, RemGnomes , TimeDec};

class Gift : public StaticObject
{
public:
	using StaticObject::StaticObject;

	virtual void handleCollision(GameObject& gameObject) override {};
	virtual void handleCollision(Mage& gameObject) override;
	virtual void handleCollision(King& gameObject) override;
	virtual void handleCollision(Thief& gameObject) override;
	virtual void handleCollision(Warrior& gameObject) override;
	virtual void handleCollision(Gnome& gameObject) override;
	GiftTypes getType() const;

protected:
	virtual void setType() = 0;
	GiftTypes m_giftType; 
};