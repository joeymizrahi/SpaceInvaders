#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#else
#error "Unrecognized configuration!"
#endif

#include "MenuState.h"
#include "MyExceptions.h"
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include "GameManager.h"
#include "Logger.h"
#include "HighScoreManager.h"

//-----------------------------------------------------------------------------
int main()
{
	srand((unsigned)time(nullptr));
	HighScoreManager::get_instance().readHighScore();

	try
	{
		std::shared_ptr<GameManager> game = std::make_shared<GameManager>();
		game->pushState(std::make_shared<MenuState>(game));  //pushing main menu
		game->gameLoop();
	}
	catch (std::exception &e)
	{
		std::string s = "Exception";
		Logger::getInstance().addLog(s + e.what());
	}

	HighScoreManager::get_instance().updateHighscoreFile();

	return EXIT_SUCCESS;
}