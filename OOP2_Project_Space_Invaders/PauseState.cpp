#include "PauseState.h"
#include "GameManager.h"

//-----------------------------------------------------------------------------
PauseState::PauseState(std::shared_ptr<GameManager> game)
{
	this->m_game = game;
	Resources::get_instance().chrono.pause();

	m_sprites.resize(3);

	sf::Sprite m_resumeButton;
	sf::Sprite m_helpButton;
	sf::Sprite m_exitButton;

	m_logo.setTexture(Resources::get_instance().getGeneralTexture(LOGO_T));
	m_logo.setOrigin(m_logo.getGlobalBounds().width / 2, 0);
	m_logo.setPosition((WINDOW_SIZE.x / 2.f), 50);

	m_resumeButton.setTexture(Resources::get_instance().getGeneralTexture(RESUME_BUTTON_T));
	m_resumeButton.setOrigin(m_resumeButton.getGlobalBounds().width / 2, m_resumeButton.getGlobalBounds().height / 2);
	m_resumeButton.setPosition((WINDOW_SIZE.x / 2.f), (WINDOW_SIZE.y / 2.f));

	m_helpButton.setTexture(Resources::get_instance().getGeneralTexture(HELP_T));
	m_helpButton.setOrigin(m_helpButton.getGlobalBounds().width / 2, m_helpButton.getGlobalBounds().height / 2);
	m_helpButton.setPosition(m_resumeButton.getPosition() + sf::Vector2f{ 0.f, 120.f });

	m_exitButton.setTexture(Resources::get_instance().getGeneralTexture(EXIT_T));
	m_exitButton.setOrigin(m_exitButton.getGlobalBounds().width / 2, m_exitButton.getGlobalBounds().height / 2);
	m_exitButton.setPosition(m_helpButton.getPosition() + sf::Vector2f{ 0.f, 120.f });

	m_sprites[inGameMenu_ID::RESUME_BUTTON] = m_resumeButton;
	m_sprites[inGameMenu_ID::HELP_IN_GAME_BUTTON] = m_helpButton;
	m_sprites[inGameMenu_ID::EXIT_IN_GAME_BUTTON] = m_exitButton;

	add("NULL", nullptr);
	add("Help", std::make_unique<Help>());
	add("Exit", std::make_unique<Exit>());
}
//-----------------------------------------------------------------------------
void PauseState::draw()
{
	m_game->m_window.draw(m_logo);

	for (auto &sprite : m_sprites)
		m_game->m_window.draw(sprite);
}
//-----------------------------------------------------------------------------
void PauseState::handleInput()
{
	sf::Event event;

	while (this->m_game->m_window.pollEvent(event))
	{
		switch (event.type)
		{
			/* Close the window */
		case sf::Event::Closed:
			this->m_game->m_window.close();
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)  //i want to remove the pause state from stack and go backwards
				m_game->m_window.close();
			else if (event.key.code == sf::Keyboard::Return)
				ResumeGame();
			break;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left) 
			{
				for (int i = 0; i < m_sprites.size(); i++)
				{
					if (m_sprites[i].getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y))
					{
						if (i == RESUME_BUTTON)
							ResumeGame();

						else if (i == EXIT_IN_GAME_BUTTON) 
						{
							m_game->popState();
							m_game->popState();
						}

						else
							m_options[i].second->execute(m_game->m_window);
					}
				}
			}
		}
	}
}
//-----------------------------------------------------------------------------
void PauseState::ResumeGame()
{
	Resources::get_instance().chrono.resume();
	m_game->popState();
}
//-----------------------------------------------------------------------------
void PauseState::add(std::string name, std::unique_ptr<Command> c)
{
	m_options.emplace_back(option(name, std::move(c)));
}