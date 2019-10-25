#pragma once
#include "Entity.h"
#include "BulletFactory.h"

class Bullet;

class Weaponable : public Entity
{
public:
	Weaponable() = default;
	virtual ~Weaponable() = default;
	virtual std::unique_ptr<Bullet> shoot() const = 0 ;
	unsigned getScore() { return m_score; }

protected:
	std::shared_ptr<BulletFactory> m_bulletFactory_ptr;
	unsigned m_score;
};