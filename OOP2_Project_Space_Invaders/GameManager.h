#pragma once
#include "MenuState.h"
#include "NewGame.h"
#include "Help.h"
#include "Exit.h"
#include "PlayingState.h"
#include <stack>

class State;

class GameManager
{
public:
	GameManager();
	~GameManager() = default;
	void pushState(std::shared_ptr<State> state);
	void popState();
	void gameLoop();
	std::shared_ptr<State> CurrentState();
	sf::RenderWindow m_window;

private:
	const sf::Time moveTime = sf::seconds((float)0.008);
	std::stack<std::shared_ptr<State>> states;
};