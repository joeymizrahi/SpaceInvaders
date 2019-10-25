#pragma once
#include "Command.h"

class HighScore : public Command
{
public:
	HighScore();
	~HighScore() = default;
	void execute(sf::RenderWindow&) override;
	void createScores();
	void draw(sf::RenderWindow&);

private:
	std::vector<sf::Text> m_scoreText;
	sf::Sprite m_highScore;
	sf::Sprite m_prevButton;
	sf::Sprite m_gameBackground;
	sf::Font m_font;
};