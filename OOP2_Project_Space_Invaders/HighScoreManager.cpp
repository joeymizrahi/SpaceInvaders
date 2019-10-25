#include "HighScoreManager.h"
#include "Resources.h"
#include <sstream>
#include <string>
#include <fstream>
#include "Logger.h"

//-----------------------------------------------------------------------------
HighScoreManager::HighScoreManager()
{
	m_highScoreFile.open("highscore.txt");
}
//-----------------------------------------------------------------------------
HighScoreManager & HighScoreManager::get_instance()
{
	static HighScoreManager instance;

	return instance;
}
//-----------------------------------------------------------------------------
//function gets existing highscore file
void HighScoreManager::readHighScore()
{
	std::stringstream ss;
	ss << m_highScoreFile.rdbuf();  //getting the buffer from the file

	do
	{
		if (ss.eof() || ss.str().size() <= 0)
			break;
		ss >> m_score >> m_name;  //getting name and score 
		m_scores.emplace(m_score, m_name);  //adding it to map of name,score
	} while (1);

	m_highScoreFile.close();  //closing file
	std::remove("highscore.txt");  //deleting it
}
//-----------------------------------------------------------------------------
//function creates new highscore file from the multimap
void HighScoreManager::updateHighscoreFile()
{
	m_highScoreFile.open("highscore.txt" ,std::ofstream::out | std::ios::trunc); 
	if (!m_highScoreFile.is_open())
		throw(FileException());

	if (m_scores.empty())
		return;

	auto it = m_scores.begin();   //getting first iterator
	if (it != m_scores.end())   //if it is the last iterator, the map is empty
	{
		for (; it != std::prev(m_scores.end()); it++)
			m_highScoreFile << (*it).first << " " << (*it).second << "\n";
	}
	m_highScoreFile << (*it).first << " " << (*it).second;
	

	
	m_highScoreFile.close();
}
//--------------------------------------------------------------
std::multimap<unsigned, std::string>& HighScoreManager::getMap()
{
	return m_scores;;
}
//-----------------------------------------------------------------------------
//adding a score, name to multimap of highscores
void HighScoreManager::updateScoreBoard(unsigned score, std::string name)
{
	m_scores.emplace(score, name);
	std::string s = "New Highscore Added: " + std::to_string(score) + name;
	Logger::getInstance().addLog(s);
}