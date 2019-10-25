#pragma once
#include "Macros.h"

class Enemy;

class MoveStrategy
{
public:
	MoveStrategy() = default;
	~MoveStrategy() = default;
	virtual void pauseClock() { }
	virtual void resumeClock() {  };
	virtual std::unique_ptr<MoveStrategy> move(Enemy&, sf::Vector2f) = 0;
};