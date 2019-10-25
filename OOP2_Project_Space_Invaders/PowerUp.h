#pragma once
#include "Entity.h"

class PowerUp : public Entity
{
public:
	PowerUp();
	~PowerUp() = default;
	virtual bool getIsActive()const { return isActive; };
	virtual void setIsActive(bool active) { isActive = active; };
	unsigned getScore()const { return m_score; }
	void setPosition(const sf::Vector2f &) { ; }
	void move(sf::Vector2f = { 0.f, 0.f }) override;    
protected:
	bool isActive;
	unsigned m_score;
};

