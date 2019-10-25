#pragma once
#include "State.h"   
#include "Resources.h"
#include "Command.h"

const int NUM_OF_BUTTONS = 4;

enum logo_ID
{
	START_BUTTON,
	HELP__BUTTON,
	HIGHSCORE_BUTTON,
	EXIT_BUTTON,
};

class MenuState :public State
{
public:
	MenuState(std::shared_ptr<GameManager> game);
	MenuState() = default;
	~MenuState() = default;
	void add(std::string, std::unique_ptr<Command>);
	void draw() override;
	void update() { ; } 
	void handleInput()override;

private:
	void loadgame();
	typedef std::pair<std::string, std::unique_ptr<Command>> option;
	std::vector<option> m_options;
	sf::Sprite m_logo;
	sf::Sprite m_gameBackground;	
	std::vector < sf::Sprite> m_sprites;
};