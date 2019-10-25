#include "MoveHorizontal.h"
#include "Enemy.h"

//-----------------------------------------------------------------------------
MoveHorizontal::MoveHorizontal(const std::pair<sf::Vector2f, sf::Vector2f> & borders) :m_borders(borders)
{
}
//-----------------------------------------------------------------------------
// moves enemy after teleport to chase the player
std::unique_ptr<MoveStrategy> MoveHorizontal::move(Enemy& alienObj, sf::Vector2f shipPos)
{
	auto &alien = alienObj.getSprite();

	if (alien.getPosition().x + alien.getTexture()->getSize().x +
		m_direction.x >= shipPos.x + 2*m_borders.second.x
		|| alien.getPosition().x + alien.getTexture()->getSize().x +
		m_direction.x <= shipPos.x + m_borders.first.x)    //alien is out of ship range
	{

		if (alien.getPosition().x + alien.getTexture()->getSize().x +
			m_direction.x - shipPos.x >= 0)  // move towards player's direction
			m_direction.x = -1;

		else
			m_direction.x = 1;
	}
	
	alien.move(m_direction);
	
	return nullptr;
}