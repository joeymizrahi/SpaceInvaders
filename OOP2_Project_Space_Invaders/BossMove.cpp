#include "BossMove.h"
#include "Enemy.h"

//-----------------------------------------------------------------------------
BossMove::BossMove(const std::pair<sf::Vector2f, sf::Vector2f> & borders) :m_borders(borders)
{
}
//-----------------------------------------------------------------------------
// moves boss enemy on the screen
std::unique_ptr<MoveStrategy> BossMove::move(Enemy& s, sf::Vector2f shipPos)
{
	auto &sprite = s.getSprite();

	if (sprite.getPosition().x + sprite.getGlobalBounds().width / 2 >= m_borders.second.x ||
		sprite.getPosition().x - sprite.getGlobalBounds().width / 2 <= m_borders.first.x)
	{
		m_direction.x *= -1;
		m_direction.y *= -1;
	}

	if (sprite.getPosition().y - sprite.getGlobalBounds().height / 2 <= m_borders.first.y ||
		sprite.getPosition().y + sprite.getGlobalBounds().height / 2 >= m_borders.second.y)
		m_direction.y *= -1;

	sprite.move(m_direction);

	return nullptr;
}