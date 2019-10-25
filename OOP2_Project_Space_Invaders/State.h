#pragma once
#include <memory>

class GameManager;

class State
{
public:
	State() = default;
	virtual~State() = default;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void handleInput() = 0;

protected:
	std::shared_ptr<GameManager> m_game;
};