#pragma once
#include "Bullet.h"

class BulletFactory;

class DefaultBullet : public Bullet
{
public:
	DefaultBullet(const bullet_pkg&);
	~DefaultBullet() = default;
	void move(sf::Vector2f = { 0.f, 0.f }) override;

private:
	static bool m_registerit;
};