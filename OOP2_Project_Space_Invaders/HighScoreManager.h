#pragma once
#include "Macros.h"
#include <fstream>

class HighScoreManager
{
public:
	static HighScoreManager& get_instance();
	void updateScoreBoard(unsigned, std::string);
	void updateHighscoreFile();
	void readHighScore();
	std::multimap<unsigned, std::string> & getMap();

private:
	HighScoreManager();
	HighScoreManager(const HighScoreManager&) = delete;  //copy c-tor
	std::multimap<unsigned, std::string> m_scores;
	std::fstream m_highScoreFile;
	std::string m_name;
	unsigned m_score;
};