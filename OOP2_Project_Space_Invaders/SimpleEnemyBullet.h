#pragma once
#include "Bullet.h"

class BulletFactory;

class SimpleEnemyBullet : public Bullet
{
public:
	SimpleEnemyBullet(const bullet_pkg&);
	~SimpleEnemyBullet() = default;
	void move(sf::Vector2f = { 0.f, 0.f }) override;

private:
	static bool m_registerit;
};