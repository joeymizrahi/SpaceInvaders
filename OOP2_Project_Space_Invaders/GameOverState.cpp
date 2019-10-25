#include "GameOverState.h"
#include "GameManager.h"
#include "HighScoreManager.h"

//-----------------------------------------------------------------------------
GameOverState::GameOverState(std::shared_ptr<GameManager> game, unsigned score)
{
	m_game = game;
	m_score = score;

	m_gameoverBackground.setTexture(Resources::get_instance().getGeneralTexture(GAMEOVER_BACKGROUND_T));

	m_yourScore.setFont(Resources::get_instance().getFont());
	m_yourScore.setString("Your Score: " + std::to_string(score));
	m_yourScore.setCharacterSize(50);
	m_yourScore.setOrigin(m_yourScore.getGlobalBounds().width / 2, 0);
	m_yourScore.setPosition((WINDOW_SIZE.x / 2) - 50, (WINDOW_SIZE.y / 2) + 40);

	m_enterName.setFont(Resources::get_instance().getFont());
	m_enterName.setString("Enter Your Name: " + m_name);
	m_enterName.setCharacterSize(50);
	m_enterName.setOrigin(m_yourScore.getGlobalBounds().width / 2, 0);
	m_enterName.setPosition((WINDOW_SIZE.x / 2) - 50, (WINDOW_SIZE.y / 2) + 140);
}
//-----------------------------------------------------------------------------
void GameOverState::draw()
{
	m_game->m_window.draw(m_gameoverBackground);
	m_game->m_window.draw(m_yourScore);
	m_game->m_window.draw(m_enterName);
}
//-----------------------------------------------------------------------------
void GameOverState::handleInput()
{
	sf::Event event;

	while (m_game->m_window.pollEvent(event))
	{
		switch (event.type)
		{
			/* Close the window */
		case sf::Event::Closed:
			m_game->m_window.close();
			break;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Return: // user finished entering name
				end = true;
				break;
			}
			break;

		case sf::Event::TextEntered:
			if (event.text.unicode == 8 && m_name.getSize() > 0)
				m_name.erase(m_name.getSize() - 1, m_name.getSize());

			if(m_name.getSize() < 10)
			{
				if ((event.text.unicode >= 32 && event.text.unicode <= 47) ||
					(event.text.unicode >= 58 && event.text.unicode <= 126))
				{
					m_name += (char)event.text.unicode;
				}
			}

			if (end)
			{
				HighScoreManager::get_instance().updateScoreBoard(m_score, m_name);
				m_game->popState();
			}
			break;
		}
		m_enterName.setString("Enter Your Name: " + m_name);
	}
}