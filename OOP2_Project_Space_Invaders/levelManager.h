#pragma once
#include "Macros.h"
#include <fstream>
#include "EnemyFactory.h"
#include "PowerUpFactory.h"

class LevelManager
{
public:
	LevelManager() = default;;
	~LevelManager() = default;;
	void setNextLevel(const int &, 
	std::vector<std::unique_ptr<Enemy>>&, 
	std::vector<std::unique_ptr<PowerUp>>&);

private:
	std::ifstream m_currLevel;
};