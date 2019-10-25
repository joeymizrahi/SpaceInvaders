#include "SmartEnemy.h"
#include "Resources.h"
#include "EnemyFactory.h"
#include "SimpleMove.h"
#include "BulletFactory.h"

//-----------------------------------------------------------------------------
SmartEnemy::SmartEnemy(const enemy_pkg& x)
{
	m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(GENERAL_TEXTURES::SMART_ENEMY_T));
	Enemy::setPosition(x.initialPos);
	m_life = 75;
	setMoveStrategy(std::make_unique<SimpleMove>());
	maxY = x.yLimit;
	m_enemyScore = 30;
	m_Sprite.setOrigin(m_Sprite.getGlobalBounds().width / 2,  m_Sprite.getGlobalBounds().height / 2);
}
//-----------------------------------------------------------------------------
void SmartEnemy::move(sf::Vector2f shipPos)
{
	if (pMoveStrategy)
	{
		auto p = pMoveStrategy->move(*this, shipPos);

		if (p)
			pMoveStrategy = std::move(p);
	}	
}
//-----------------------------------------------------------------------------
std::unique_ptr<Bullet> SmartEnemy::shoot()const
{
	struct bullet_pkg shipBullet;
	shipBullet.initialPos =  { m_Sprite.getPosition().x   ,m_Sprite.getPosition().y + m_Sprite.getGlobalBounds().height/2  };
	shipBullet.heroBullet = false;
	shipBullet.driection = { 0,1 };
	shipBullet.damage = -35;
	return m_bulletFactory_ptr->create("simple enemy bullet", shipBullet);
}
//-----------------------------------------------------------------------------
void SmartEnemy::setMoveStrategy(std::unique_ptr<MoveStrategy> p)
{
	pMoveStrategy = std::move(p);
}
//-----------------------------------------------------------------------------
//registering the entity to map
bool SmartEnemy::m_registerit = EnemyFactory::registerit(ENEMY_CHARS::SMART_ENEMY_C,
	[](const enemy_pkg& x) -> std::unique_ptr<Enemy> { return std::make_unique<SmartEnemy>(x); });