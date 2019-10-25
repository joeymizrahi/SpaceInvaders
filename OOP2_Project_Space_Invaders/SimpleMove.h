#pragma once
#include "MoveStrategy.h"

class SimpleMove : public MoveStrategy
{
public:
	SimpleMove() = default;
	~SimpleMove() = default;
	std::unique_ptr<MoveStrategy> move(Enemy&, sf::Vector2f) override;

private:
	sf::Vector2f m_direction = { 1, 0 };
	sf::Vector2i stepsTaken;
	int y = 20;
};