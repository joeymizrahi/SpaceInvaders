#include "ShieldPowerUp.h"
#include "PowerUpFactory.h"

//-----------------------------------------------------------------------------
ShieldPowerUp::ShieldPowerUp(const powerUp_pkg& pkg)
{
	m_Sprite.setPosition(pkg.initialPos);
	m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(GENERAL_TEXTURES::CLUSTER_BULLET_POWERUP_T));
	m_Sprite.setOrigin((sf::Vector2f)(m_Sprite.getTexture()->getSize() / 2u));
	m_score = 150; 
}
//-----------------------------------------------------------------------------
//registering the entity to map
bool ShieldPowerUp::m_registerit = PowerUpFactory::registerit(POWER_UP_CHARS::SHIELD_C,
	[](const powerUp_pkg& x) -> std::unique_ptr<PowerUp> { return std::make_unique<ShieldPowerUp>(x); });