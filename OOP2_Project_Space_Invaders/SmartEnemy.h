#pragma once
#include "Enemy.h"
#include "Bullet.h"

class BulletFactory;

class SmartEnemy :public Enemy
{
public:
	SmartEnemy(const enemy_pkg&);
	void move(sf::Vector2f) override;
	void setMoveStrategy(std::unique_ptr<MoveStrategy>) override;
	std::unique_ptr<Bullet> shoot()const override;

private:
	
	sf::Vector2f m_direction = { 1, 0 };
	static bool m_registerit;

};