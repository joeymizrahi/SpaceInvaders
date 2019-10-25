#pragma once
#include "EnemyFactory.h"
#include "levelManager.h"
#include "PowerUp.h"
#include "State.h"

class Ship;
class Enemy;
class Bullet;

class PlayingState : public State
{
public:
	PlayingState(std::shared_ptr<GameManager> game);
	PlayingState() = default;
	~PlayingState() = default;

	void update(sf::RenderWindow&);
	void nextLevel();
	void updateShip( sf::Event&);
	void updateInnerHealthBar();
	void draw() override;
	void update()override;
	void handleInput() override;

private:
	void activateStart();
	void PauseGame(); 
	void moveAll();
	void alienShoot();
	void teleportAlien();
	void activatePowerUp();
	void collisions();
	void scrollBackground(sf::RenderWindow&);
	void gameOverScreen();

	std::unique_ptr<Ship> m_ship;
	std::vector<std::unique_ptr<Enemy>> m_enemies;
	std::vector<std::unique_ptr<Bullet>> m_bullets;
	std::vector<std::unique_ptr<PowerUp>> m_powerUps;
	std::vector<sf::Sprite> m_lives;

	//EnemyFactory m_factory;
	LevelManager m_levelmanager;

	sf::Sprite m_gameBackground;
	sf::Sprite m_gameBackground2;
	sf::Sprite m_healthBar;
	sf::Sprite m_innerHealthBar;
	sf::Sprite m_shipSprite;
	sf::Text m_gameScore;
	sf::Text m_waveText;

	int m_teleported_enemy = -1;
	int m_level;
	const sf::Time moveTime = sf::seconds((float)0.008);
	const sf::Time shootTime = sf::seconds(0.5f);
	const sf::Time powerUpTime = sf::seconds(5.f);
	const sf::Time teleportTime = sf::seconds(0.2f);
	sf::Time updateTime = sf::seconds(0);
	sf::Time totalShootTime = sf::seconds(0.f);
	sf::Time totalpowerUpTime = sf::seconds(0.f);
	sf::Time TOD = sf::seconds(0.f);
	sf::Clock shoot_clock;
};