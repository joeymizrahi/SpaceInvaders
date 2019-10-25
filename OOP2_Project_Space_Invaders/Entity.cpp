#include "Entity.h"
#include "Macros.h"

//-----------------------------------------------------------------------------
sf::Vector2f Entity::getSpriteSize()const 
{
	return { m_Sprite.getGlobalBounds().width,m_Sprite.getGlobalBounds().height };
}
//-----------------------------------------------------------------------------
void Entity::draw(sf::RenderWindow & window) 
{
	window.draw(m_Sprite);
}
//-----------------------------------------------------------------------------
void Entity::setAliveOrDead(const bool &b)
{
	isAlive = b;
}