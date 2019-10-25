#include "SimpleEnemy.h"
#include "EnemyFactory.h"
#include "Resources.h"
#include "BulletFactory.h"
#include "SimpleMove.h"

//-----------------------------------------------------------------------------
SimpleEnemy::SimpleEnemy(const enemy_pkg& x)
{
	m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(GENERAL_TEXTURES::SIMPLE_ENEMY_T));
	Enemy::setPosition(x.initialPos);
	m_life = 50;   
	setMoveStrategy(std::make_unique<SimpleMove>());    
	maxY = x.yLimit;
	m_enemyScore = 20;
	m_Sprite.setOrigin(m_Sprite.getGlobalBounds().width / 2, m_Sprite.getGlobalBounds().height / 2);
}
//-----------------------------------------------------------------------------
std::unique_ptr<Bullet> SimpleEnemy::shoot()const
{
	struct bullet_pkg shipBullet;
	shipBullet.initialPos = { m_Sprite.getPosition().x   ,m_Sprite.getPosition().y + m_Sprite.getGlobalBounds().height / 2 };
	shipBullet.heroBullet = false;
	shipBullet.driection = { 0,1 };
	shipBullet.damage = -25;
	return m_bulletFactory_ptr->create(SIMPLE_ENEMY_BULLET_STRING, shipBullet);
}
//-----------------------------------------------------------------------------
void SimpleEnemy::move(sf::Vector2f shipPos)
{
	if (pMoveStrategy)
	{
		auto p = pMoveStrategy->move(*this, shipPos);

		if (p)
			pMoveStrategy = std::move(p);
	}
}
//-----------------------------------------------------------------------------
void SimpleEnemy::wallCollision()
{
	m_direction.x *= -1;
	m_Sprite.move(0, 20);
}
//-----------------------------------------------------------------------------
void SimpleEnemy::setMoveStrategy(std::unique_ptr<MoveStrategy> move_ptr)
{
	pMoveStrategy = std::move(move_ptr);
}
//-----------------------------------------------------------------------------
//registering the entity to map
bool SimpleEnemy::m_registerit = EnemyFactory::registerit(ENEMY_CHARS::SIMPLE_ENEMY_C,
	[](const enemy_pkg& x) -> std::unique_ptr<Enemy> { return std::make_unique<SimpleEnemy>(x); });