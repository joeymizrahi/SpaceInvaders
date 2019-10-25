#include "HighScore.h"
#include "Resources.h"
#include "HighScoreManager.h"

//-----------------------------------------------------------------------------
HighScore::HighScore()
{
	m_prevButton.setTexture(Resources::get_instance().getGeneralTexture(PREV_T));
	m_gameBackground.setTexture(Resources::get_instance().getGeneralTexture(GAME_BACKGROUND_T));
	m_highScore.setTexture(Resources::get_instance().getGeneralTexture(HIGHSCORE_TITLE_T));
	m_highScore.setOrigin(m_highScore.getGlobalBounds().width / 2, 0);
	m_highScore.setPosition(WINDOW_SIZE.x / 2, 100);
	m_prevButton.setPosition(10, 10);
}
//-----------------------------------------------------------------------------
void HighScore::execute(sf::RenderWindow& window)
{
	sf::Event event;
	createScores();

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				return;

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (m_prevButton.getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y))
						return;
				}
			}
		}
		window.clear();
		draw(window);
		window.display();
	}
}
//-----------------------------------------------------------------------------
void HighScore::createScores()
{
	int place = 0;
	sf::Text scoreText;
	scoreText.setFont(Resources::get_instance().getFont());
	auto scoresMap = HighScoreManager::get_instance().getMap();
	std::multimap<unsigned, std::string>::reverse_iterator rit;

	m_scoreText.clear();  //clearing vector of texts so we dont add what was already there

	//running through map and creating texts
	for (rit = scoresMap.rbegin(); rit != scoresMap.rend(); ++rit)
	{
		scoreText.setString(rit->second + " " + std::to_string(rit->first));
		scoreText.setPosition(300.f, (50.f * place) + 300.f);
		m_scoreText.push_back(scoreText);
		place++;
	}
}
//-----------------------------------------------------------------------------
void HighScore::draw(sf::RenderWindow& window)
{
	window.clear();
	window.draw(m_gameBackground);
	window.draw(m_highScore);
	for (auto &score : m_scoreText)
		window.draw(score);
	window.draw(m_prevButton);
}