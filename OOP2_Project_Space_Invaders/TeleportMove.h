#pragma once
#include "MoveStrategy.h"
#include "Chronometer.hpp"

class TeleportMove : public MoveStrategy
{
public:
	TeleportMove(std::unique_ptr<MoveStrategy>);
	~TeleportMove() = default;
	void pauseClock()override;
	void resumeClock()override;
	std::unique_ptr<MoveStrategy> move(Enemy&, sf::Vector2f) override;

private:
	sf::Sprite m_teleport_sprite;
	std::unique_ptr<MoveStrategy> m_moveStrategy;  //to hold his current move strategy, so he can move while being teleported
	sftools::Chronometer teleportAnimation;
};