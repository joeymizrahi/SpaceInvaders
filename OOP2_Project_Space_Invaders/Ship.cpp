#include "Ship.h"
#include "Resources.h"
#include "BulletFactory.h"

//-----------------------------------------------------------------------------
Ship::Ship(sf::Vector2f start_pos) : m_life(3), m_health(100)
{
	m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(GENERAL_TEXTURES::DEFAULT_HERO_T));
	m_Sprite.setPosition(start_pos);
	m_Sprite.setOrigin((sf::Vector2f)(m_Sprite.getTexture()->getSize() / 2u));

	m_bulletFactory_ptr = std::make_shared < BulletFactory>();
	m_bullet_string = DEFAULT_HERO_BULLET_STRING;
}
//-----------------------------------------------------------------------------
void Ship::move(sf::Vector2f offset)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if(m_shielded)
			m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(GENERAL_TEXTURES::SHIELD_SHIP_LEFT_T));
		else
			m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(GENERAL_TEXTURES::SHIP_LEFT_T));
		offset = { -3.f, 0.f };
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (m_shielded)
			m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(GENERAL_TEXTURES::SHIELD_SHIP_RIGHT_T));
		else
			m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(GENERAL_TEXTURES::SHIP_RIGHT_T));
		offset = { 3.f, 0.f };
	}
	else
	{
		if (m_shielded)
			m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(GENERAL_TEXTURES::SHIELD_SHIP_T));
		else 
			m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(GENERAL_TEXTURES::DEFAULT_HERO_T));
	}
		
	if (m_Sprite.getPosition().x + m_Sprite.getTexture()->getSize().x / 2 +
		offset.x >= WINDOW_SIZE.x ||
		m_Sprite.getPosition().x - m_Sprite.getTexture()->getSize().x / 2 + offset.x <= 0)
		return;

	m_Sprite.move(offset);

	if (m_Sprite.getTextureRect().top < 0)
		return;
}
//-----------------------------------------------------------------------------
std::unique_ptr<Bullet> Ship::shoot() const
{
	Resources::get_instance().play(MUSIC_ID::SHOOT_M);
	struct bullet_pkg shipBullet;
	shipBullet.initialPos = { m_Sprite.getPosition().x  ,m_Sprite.getPosition().y - m_Sprite.getGlobalBounds().height / 2 };
	shipBullet.heroBullet = true;
	shipBullet.driection = { 0,-1 };
	shipBullet.damage = -25; 

	return m_bulletFactory_ptr->create(m_bullet_string, shipBullet);
}
//-----------------------------------------------------------------------------
float Ship::getHealthFromShip()
{
	return m_health;
}
//-----------------------------------------------------------------------------
void Ship::setHealthToShip(float health)
{
	if(!m_shielded)
		m_health += health;

	if (m_health <= 0)
	{
		m_life--;
		m_health = MAX_HEALTH;
	}	
}
//-----------------------------------------------------------------------------
int Ship::getShipLife()
{
	return m_life;
}
//-----------------------------------------------------------------------------
void Ship::draw(sf::RenderWindow &window)
{
	if (m_shielded)
	{
		auto p = m_Sprite.getTextureRect();
		p.width = Resources::get_instance().getGeneralTexture(GENERAL_TEXTURES::SHIELD_SHIP_RIGHT_T).getSize().x;
		p.height = Resources::get_instance().getGeneralTexture(GENERAL_TEXTURES::SHIELD_SHIP_RIGHT_T).getSize().y;
		m_Sprite.setTextureRect(p);
		m_Sprite.setOrigin((sf::Vector2f)(m_Sprite.getTexture()->getSize() / 2u));

		
		const static sf::Time shieldTime = sf::seconds(20.f);
		static bool resetClock = false;

		if (shieldClock.getElapsedTime() > shieldTime)  
		{
			m_shielded = false;
			resetClock = true;
		}

		if (resetClock)
		{
			shieldClock.restart();
			resetClock = false;
		}
	}
	else
	{
		auto p = m_Sprite.getTextureRect();
		p.width = Resources::get_instance().getGeneralTexture(GENERAL_TEXTURES::DEFAULT_HERO_T).getSize().x;
		p.height = Resources::get_instance().getGeneralTexture(GENERAL_TEXTURES::DEFAULT_HERO_T).getSize().y;
		m_Sprite.setTextureRect(p);
		m_Sprite.setOrigin((sf::Vector2f)(m_Sprite.getTexture()->getSize() / 2u));
	}

	window.draw(m_Sprite);
}
//-----------------------------------------------------------------------------
void Ship::addScore(unsigned score) 
{
	m_score += score;
}