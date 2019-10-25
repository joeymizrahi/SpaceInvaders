#pragma once
#include "Bullet.h"

class BulletFactory;

class WaveBullet : public Bullet
{
public:
	WaveBullet(const bullet_pkg& pkg);
	~WaveBullet() = default;;
	void move(sf::Vector2f = { 0.f, 0.f }) override;

private:
	static bool m_registerit;
};