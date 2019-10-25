#pragma once
#include "State.h"
#include "Macros.h"

class GameOverState : public State
{
public:
	GameOverState(std::shared_ptr<GameManager> game, unsigned score);
	GameOverState() = default;
	~GameOverState() = default;
	void draw();
	void update() { ; }
	void handleInput();

private:
	sf::Sprite m_gameoverBackground;
	sf::Text m_yourScore;
	sf::Text m_enterName;
	sf::String m_name;
	unsigned m_score;
	bool end = false;
};