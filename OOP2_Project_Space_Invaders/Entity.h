#pragma once
#include "Resources.h"

class Entity
{
public:
	Entity() = default;
	virtual~Entity() = default;
	virtual void setPosition(const sf::Vector2f &pos) = 0;
	virtual void resetMove() { m_Sprite.setPosition(m_last_move); }
	virtual void draw(sf::RenderWindow & window);
	virtual void move(sf::Vector2f = {0.f, 0.f}) {};
	virtual void wallCollision() {};
	virtual void setAliveOrDead(const bool&);
	virtual sf::Vector2f getPosition() { return m_Sprite.getPosition(); }
	virtual sf::FloatRect getRect() { return m_Sprite.getGlobalBounds(); }
	inline sf::Vector2f getSpriteSize() const ;
	sf::Vector2f getPosition()const { return m_Sprite.getPosition(); }
	bool getIsAlive() { return isAlive; }

protected:
	sf::Sprite m_Sprite; 
	sf::Vector2f m_last_move;
	bool isAlive = true;
};