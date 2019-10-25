#include "SimpleMove.h"
#include "Enemy.h"
#include "MoveHorizontal.h"

//-----------------------------------------------------------------------------
// general (default) movement of the enemies
std::unique_ptr<MoveStrategy> SimpleMove::move(Enemy& s, sf::Vector2f shipPos)
{
	static float a = 1;
	static bool floorHit = false;
	auto &sprite = s.getSprite();

	if (stepsTaken.x > 200)  //if he took over 200 steps, switch direction and go down
	{
		m_direction.x *= -1;
		sprite.move(0, (float)y);
		stepsTaken.y += 20;
		stepsTaken.x = -380;
	}
	if (stepsTaken.y >= 40)  // he took more than 40 steps down/up switch y direction
	{
		y *= -1;
		stepsTaken.y = 0;
	}
	else   //in window range move left/right
	{
		m_direction.y = 0;
		sprite.move(m_direction);
		stepsTaken.x++;
	}
	return nullptr;
}