#include "PowerUp.h"

//-----------------------------------------------------------------------------
PowerUp::PowerUp() :isActive(false)
{
}
//-----------------------------------------------------------------------------
void PowerUp::move(sf::Vector2f)
{
	m_Sprite.move({ 0, 1 });
	m_Sprite.rotate(1);
}