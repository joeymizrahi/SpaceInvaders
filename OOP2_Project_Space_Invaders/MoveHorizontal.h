#pragma once
#include "MoveStrategy.h"

class MoveHorizontal : public MoveStrategy
{
public:
	MoveHorizontal(const std::pair<sf::Vector2f, sf::Vector2f> &);
	~MoveHorizontal() = default;
	std::unique_ptr<MoveStrategy> move(Enemy& , sf::Vector2f );

private:
	const std::pair<sf::Vector2f, sf::Vector2f>  m_borders;
	sf::Vector2f m_direction = { 1, 0 };
};