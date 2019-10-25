#pragma once
#include "Enemy.h"
#include "Resources.h"

class BulletFactory;

class BossEnemy : public Enemy
{
public:
	BossEnemy(const enemy_pkg&);
	BossEnemy() = default;
	~BossEnemy() = default;
	void move(sf::Vector2f) override;
	void draw(sf::RenderWindow & window) override;
	void setMoveStrategy(std::unique_ptr<MoveStrategy>) override { ; }
	std::unique_ptr<Bullet> shoot()const override;
	sf::FloatRect getRect() override;

private:
	int m_bossFrame = 1;
	static bool m_registerit;
	sf::Vector2f m_direction = { 1, 0 };
	sf::Time TOD = sf::seconds(0.f);
	std::shared_ptr<BulletFactory> m_bulletFactory_ptr;
};