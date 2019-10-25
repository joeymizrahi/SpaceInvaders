#pragma once
#include "Enemy.h"
#include "Resources.h"

class BulletFactory;

class SimpleEnemy : public Enemy
{
public:
	SimpleEnemy(const enemy_pkg&);
	~SimpleEnemy() = default;
	void move(sf::Vector2f) override;
	void wallCollision() override;
	void setMoveStrategy(std::unique_ptr<MoveStrategy>) override;
	std::unique_ptr<Bullet> shoot()const override;

private:
	static bool m_registerit;
	//std::shared_ptr<BulletFactory> m_bulletFactory_ptr;
	sf::Vector2f m_direction = { 1, 0 };
};