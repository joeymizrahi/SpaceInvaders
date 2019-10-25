#pragma once
#include "State.h"
#include "Macros.h"
#include "Command.h"
class Ship;

enum inGameMenu_ID
{
	RESUME_BUTTON,
	HELP_IN_GAME_BUTTON,
	EXIT_IN_GAME_BUTTON
};

class PauseState : public State
{
public:
	PauseState(std::shared_ptr<GameManager> game);
	PauseState() = default;
	~PauseState() = default;
	void draw();
	void update() { ; }
	void handleInput();
	void add(std::string, std::unique_ptr<Command>);

private:
	void ResumeGame();
	typedef std::pair<std::string, std::unique_ptr<Command>> option;
	std::vector<option> m_options;
	std::vector < sf::Sprite> m_sprites;
	sf::Sprite m_logo;
};