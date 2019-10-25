#pragma once
#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet() = default;
	virtual ~Bullet() = default;
	virtual void setPosition(const sf::Vector2f &pos) { ; }
	void setDirection(const sf::Vector2f& new_dir);
	void setOwner(bool heroBullet);
	bool isHeroBullet() { return m_heroBullet; }
	float getDamage() { return m_damage; }

protected:
	sf::Vector2f m_direction;
	bool m_heroBullet;
	float m_damage;
	std::vector<std::unique_ptr<Bullet>>  m_bullets;
};