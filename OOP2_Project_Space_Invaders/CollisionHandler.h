#pragma once
#include "Entity.h"
#include <iostream>
#include "Logger.h"
struct UnknownCollision
{
	UnknownCollision(Entity& a, Entity& b) : first(a), second(b)
	{
		std::string s =
			"Unknown collision of " + std::string(typeid(a).name()) + " and "
			+ typeid(b).name() + "\n";
		Logger::getInstance().addLog(s);
	}
	Entity& first;
	Entity& second;
};
bool isCollision(const sf::FloatRect&, const sf::FloatRect&);
void processCollision(Entity& object1, Entity& object2);