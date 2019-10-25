#include "TeleportMove.h"
#include "Resources.h"
#include "MoveHorizontal.h"
#include "Enemy.h"
#include "SimpleMove.h"

//-----------------------------------------------------------------------------
TeleportMove::TeleportMove(std::unique_ptr<MoveStrategy> p) 
{
	m_moveStrategy = std::move(p);   //we move the current way he is moving, so we need to get his strategy
	m_teleport_sprite.setTexture(Resources::get_instance().getGeneralTexture(GENERAL_TEXTURES::TELEPORT_T));
	m_teleport_sprite.setOrigin(m_teleport_sprite.getGlobalBounds().width / 2, m_teleport_sprite.getGlobalBounds().height / 2);
	teleportAnimation.reset(true);
}
//-----------------------------------------------------------------------------
void TeleportMove::pauseClock()  //pause animation when in pause state 
{
	teleportAnimation.pause();
}
//-----------------------------------------------------------------------------
void TeleportMove::resumeClock()
{
	teleportAnimation.resume();
}
//-----------------------------------------------------------------------------
std::unique_ptr<MoveStrategy> TeleportMove::move(Enemy& alien, sf::Vector2f shipPos)
{
	const static sf::Time animationTime = sf::seconds(2.f);  //teleport animation will last this long
	auto &m_Sprite = alien.getSprite();  //getting the sprite of the alien to change
	static bool resetClock = false;  //to know when to reset animation clock
	m_teleport_sprite.setPosition(m_Sprite.getPosition());  //setting animation of teleport on enemy

	if (resetClock) 
	{
		teleportAnimation.reset(true);
		resetClock = false;
	}
	if (teleportAnimation.getElapsedTime() <= animationTime)  //if we still in animation
	{
		m_teleport_sprite.rotate(-1);  
		m_moveStrategy->move(alien, shipPos);   //moving the way he was b4
		m_Sprite.scale(0.99f, 0.99f);  //scaling the alien, so it looks like hes being sucked into teleport
		alien.setTeleport(true);  
	}
	else
	{
		m_Sprite.setScale(1, 1);  //resetting the scale to the original
		m_Sprite.setPosition(shipPos.x - 30, shipPos.y - 200);  //setting the teleported alien above the hero
		resetClock = true;
		alien.setTeleport(false); 
		return std::make_unique<MoveHorizontal>(std::make_pair(sf::Vector2f{ -60, 0 }, sf::Vector2f{ 60, 0 }));  //changing his move strategy
	}
	return nullptr;
}