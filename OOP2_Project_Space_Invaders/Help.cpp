#include "Help.h"
#include "Resources.h"

//-----------------------------------------------------------------------------
Help::Help()
{
	m_prevButton.setTexture(Resources::get_instance().getGeneralTexture(PREV_T));
	m_gameBackground.setTexture(Resources::get_instance().getGeneralTexture(GAME_BACKGROUND_T));
	m_instructions.setTexture(Resources::get_instance().getGeneralTexture(INSTRUCTIONS_T));
	m_instructions.setPosition(0, 50);
	m_prevButton.setPosition(10, 10);
}
//-----------------------------------------------------------------------------
void Help::execute(sf::RenderWindow& window)
{
	sf::Event event;

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
		window.draw(m_gameBackground);
		window.draw(m_instructions);
		window.draw(m_prevButton);
		window.display();
	}
}