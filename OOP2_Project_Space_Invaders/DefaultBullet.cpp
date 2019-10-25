#include "DefaultBullet.h"
#include "BulletFactory.h"
#include "Resources.h"

//-----------------------------------------------------------------------------
DefaultBullet::DefaultBullet(const bullet_pkg& pkg)
{
	m_Sprite.setPosition(pkg.initialPos);
	m_heroBullet = pkg.heroBullet;
	m_direction = pkg.driection;
	m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(GENERAL_TEXTURES::DEFAULT_BULLET_T));;
	m_Sprite.setOrigin((sf::Vector2f)(m_Sprite.getTexture()->getSize() / 2u));
	m_damage = pkg.damage;
}
//-----------------------------------------------------------------------------
void DefaultBullet::move(sf::Vector2f )
{
	m_Sprite.move(m_direction.x*4, m_direction.y * 4);
}
//-----------------------------------------------------------------------------
bool DefaultBullet::m_registerit = BulletFactory::registerit(DEFAULT_HERO_BULLET_STRING,  
	[](const bullet_pkg& x) -> std::unique_ptr<Bullet> { return std::make_unique<DefaultBullet>(x); });