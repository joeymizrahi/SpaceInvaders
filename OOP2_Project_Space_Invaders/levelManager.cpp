#include "levelManager.h"
#include <sstream>
#include "PowerUpFactory.h"
#include "EnemyFactory.h"

//-----------------------------------------------------------------------------
void LevelManager::setNextLevel(const int & level,
	std::vector<std::unique_ptr<Enemy>>& m_enemies,
	std::vector<std::unique_ptr<PowerUp>>& m_powerUps)
{
	std::string file_path;
	std::stringstream ss;
	int rows, cols, power_ups;
	char c;

	file_path = "Levels/Level_" + std::to_string(level) + ".txt"; // loads the level file path

	m_currLevel.open(file_path);

	if (!m_currLevel.is_open())
		throw(std::exception());

	ss << m_currLevel.rdbuf();  //putting all the chars into string stream	

	m_currLevel.close();

	ss >> c;
	rows = std::stoi(std::string(1, c)); //rows of enemies						  
	ss >> c;
	cols = std::stoi(std::string(1, c)); // columns of enemies
	ss >> power_ups;

	// creates power-ups (through PowerUp Factory) that will be given during the game
	for (int i = 0; i < power_ups; i++)
	{
		ss >> c;
		powerUp_pkg p_pkg;
		p_pkg.initialPos = { float(fmod(rand(), WINDOW_SIZE.x - 100) + 100) ,-20.f };
		if (auto p = PowerUpFactory::create((POWER_UP_CHARS)c, p_pkg))
			m_powerUps.push_back(std::move(p));
	}

	// creates the enemies objects through Enemy Factory
	for (int row = 0,r = rows; !ss.eof() && row < rows; row++,r--)
	{
		for (int col = 0; col < cols; col++)
		{
			int currCell = row * cols + col;
			ss >> c;
			enemy_pkg pkg;
			pkg.initialPos = { (float)col, (float)row };
			pkg.yLimit = WINDOW_SIZE.y - 350 - (r*30);

			if (auto p = EnemyFactory::create((ENEMY_CHARS)c, pkg))
				m_enemies.push_back(std::move(p));

		}
	}
}