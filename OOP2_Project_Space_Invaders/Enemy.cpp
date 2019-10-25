#include "Enemy.h"
#include "TeleportMove.h"
#include "MoveHorizontal.h"
#include "SimpleMove.h"

//-----------------------------------------------------------------------------
Enemy::Enemy()
{
	your_turn = true;

	m_teleport_sprite.setTexture(Resources::get_instance().getGeneralTexture(GENERAL_TEXTURES::TELEPORT_T));
	m_teleport_sprite.setOrigin(m_teleport_sprite.getGlobalBounds().width / 2, m_teleport_sprite.getGlobalBounds().height / 2);

	m_explosion.setTexture(Resources::get_instance().getGeneralTexture(EXPLOSION_T));
	m_explosion.setOrigin(m_explosion.getGlobalBounds().width / 2, m_explosion.getGlobalBounds().height / 2);
}
//-----------------------------------------------------------------------------
void Enemy::setPosition(const sf::Vector2f & start_pos)
{
	sf::Vector2f pos(start_pos.x * m_Sprite.getGlobalBounds().width * 1.5f + 400.f,
		start_pos.y * m_Sprite.getGlobalBounds().height * 1.5f + 30.f);

	m_Sprite.setPosition(pos);
}
//-----------------------------------------------------------------------------
void Enemy::setHealthToEnemy(float d)
{
	m_life += d;

	if (m_life <= 0)
	{
		TOD = Resources::get_instance().chrono.getElapsedTime(); //last time alive (TOD)
		isAlive = false;
		m_score = m_enemyScore;

		Resources::get_instance().play(MUSIC_ID::EXPLOSION_M);
	}
}
//-----------------------------------------------------------------------------
void Enemy::destroyEnemy(sf::RenderWindow& window)
{
	m_score = 0;
	if (Resources::get_instance().chrono.getElapsedTime().asSeconds() >= TOD.asSeconds() + (0.165f)*m_explosionFrame)
	{
		m_explosion.setTextureRect(sf::IntRect(m_explosionFrame * 57, 0, 57, 57));
		m_explosion.setOrigin(m_explosion.getGlobalBounds().width / 2, m_explosion.getGlobalBounds().height / 2);
		m_explosion.setPosition(m_Sprite.getPosition());
		window.draw(m_explosion);
		
		if (Resources::get_instance().chrono.getElapsedTime().asSeconds() >= TOD.asSeconds() + (0.165f)*(m_explosionFrame + 1))
			m_explosionFrame++;
	}
	
	if (m_explosionFrame == 12)
	{
		m_explosionFrame = 0;
		m_burried = true;


		if (pMoveStrategy && typeid(*pMoveStrategy) == typeid(MoveHorizontal))
		{
			your_turn = true;
			pMoveStrategy = nullptr;
		}
	}
}
//-----------------------------------------------------------------------------
void Enemy::draw(sf::RenderWindow &window)
{
	if (is_teleporting)
	{
		m_teleport_sprite.setPosition(m_Sprite.getPosition());
		m_teleport_sprite.rotate(1.5);
		window.draw(m_teleport_sprite);
	}
	window.draw(m_Sprite);
}

bool Enemy::your_turn = true;