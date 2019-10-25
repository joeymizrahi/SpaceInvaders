#pragma once
#include <SFML\Graphics.hpp>

class Command
{
public:
	virtual void execute(sf::RenderWindow&) = 0;
};