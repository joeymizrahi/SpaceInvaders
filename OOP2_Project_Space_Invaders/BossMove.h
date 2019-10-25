#pragma once
#include "MoveStrategy.h"

class BossMove : public MoveStrategy
{
public:
	BossMove(const std::pair<sf::Vector2f, sf::Vector2f> & borders);
	BossMove() = default;
	~BossMove() = default;
	std::unique_ptr<MoveStrategy> move(Enemy&, sf::Vector2f) override;

private:
	sf::Vector2f m_direction = { 1, 0.5 };
	const std::pair<sf::Vector2f, sf::Vector2f>  m_borders;
};