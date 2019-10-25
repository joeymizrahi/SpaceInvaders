#include "SimpleEnemyBullet.h"
#include "BulletFactory.h"
#include "Resources.h"

//-----------------------------------------------------------------------------
SimpleEnemyBullet::SimpleEnemyBullet(const bullet_pkg& pkg)
{
	m_Sprite.setPosition(pkg.initialPos);
	m_heroBullet = pkg.heroBullet;
	m_direction = pkg.driection;
	m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(GENERAL_TEXTURES::SIMPLE_ENEMY_BULLET_T));;
	m_Sprite.setOrigin((sf::Vector2f)(m_Sprite.getTexture()->getSize() / 2u));
	m_damage = pkg.damage;
}
//-----------------------------------------------------------------------------
void SimpleEnemyBullet::move(sf::Vector2f )
{
	if (m_Sprite.getPosition().x + m_Sprite.getTexture()->getSize().x / 2 +
		m_direction.x >= WINDOW_SIZE.x ||
		m_Sprite.getPosition().x - m_Sprite.getTexture()->getSize().x / 2 + m_direction.x <= 0 ||
		m_Sprite.getPosition().y <=0 || m_Sprite.getPosition().y >= WINDOW_SIZE.y)
		isAlive = false;

	m_Sprite.move(m_direction.x*4, m_direction.y * 4);
}
//-----------------------------------------------------------------------------
bool SimpleEnemyBullet::m_registerit = BulletFactory::registerit(SIMPLE_ENEMY_BULLET_STRING,
	[](const bullet_pkg& x) -> std::unique_ptr<Bullet> { return std::make_unique<SimpleEnemyBullet>(x); });