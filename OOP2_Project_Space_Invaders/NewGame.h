#pragma once
#include "Command.h"

class NewGame : public Command
{
public:
	NewGame() = default;
	~NewGame() = default;
	void execute(sf::RenderWindow&) override;
};