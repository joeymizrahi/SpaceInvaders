#pragma once
#include "Command.h"

class Help : public Command
{
public:
	Help();
	~Help() = default;
	void execute(sf::RenderWindow&) override;

private:
	sf::Sprite m_prevButton;
	sf::Sprite m_gameBackground;
	sf::Sprite m_instructions;
};