#include "PlayingState.h"
#include "BulletFactory.h"
#include "Resources.h"
#include "CollisionHandler.h"
#include "TeleportMove.h"
#include "GameManager.h"
#include "Ship.h"
#include "Bullet.h"
#include "Enemy.h"
#include "PauseState.h"
#include "MenuState.h"
#include "GameOverState.h"

//-----------------------------------------------------------------------------
PlayingState::PlayingState(std::shared_ptr<GameManager> game) :m_level(0)
{
	activateStart();
	m_game = game;

	m_gameBackground.setTexture(Resources::get_instance().getGeneralTexture(GAME_BACKGROUND_T));
	m_gameBackground2.setTexture(Resources::get_instance().getGeneralTexture(GAME_BACKGROUND_T));
	m_gameBackground2.setPosition(0, (m_gameBackground.getPosition().y - m_gameBackground.getTexture()->getSize().y) - 1);

	m_ship = std::make_unique<Ship>(sf::Vector2f{ WINDOW_SIZE.x / 2.f, WINDOW_SIZE.y - 100.f });

	m_healthBar.setTexture(Resources::get_instance().getGeneralTexture(HEALTH_BAR_T));
	m_healthBar.setPosition(50, WINDOW_SIZE.y - 60);
	m_healthBar.setScale(1.5f, 1.5f);

	m_innerHealthBar.setTexture(Resources::get_instance().getGeneralTexture(INNER_HEALTH_BAR_T));
	m_innerHealthBar.setPosition(m_healthBar.getPosition() + sf::Vector2f{ 14.f,10.f });
	m_innerHealthBar.setScale(1.5f, 1.5f);

	for (int i = 0; i < m_ship->getShipLife(); i++)
	{
		m_shipSprite.setTexture(Resources::get_instance().getGeneralTexture(DEFAULT_HERO_T));
		m_shipSprite.setOrigin(m_shipSprite.getGlobalBounds().width / 2, m_shipSprite.getGlobalBounds().height / 2);
		m_lives.push_back(m_shipSprite);
		m_lives[i].setPosition(80 + m_healthBar.getGlobalBounds().width + (i * 50), WINDOW_SIZE.y - m_healthBar.getGlobalBounds().height + 10);
		m_lives[i].setScale(0.7f, 0.7f);
	}

	m_gameScore.setFont(Resources::get_instance().getFont());
	m_gameScore.setPosition(20, 10);

	nextLevel();  //starting the first level
}
//-----------------------------------------------------------------------------
void PlayingState::update(sf::RenderWindow& window)
{
	//moving...........................
	moveAll();
	//.....................................

	//shooting......................................
	alienShoot();
	//----------------------------

	//choosing random alien to be teleported.....................
	teleportAlien();
	//----------------------------

	//getting random power up to activate.................
	activatePowerUp();
	//--------------------------------

	//checking if next level should be loaded
	if (m_enemies.size() <= 0) {  
		if (m_level < MAX_LEVELS)
			nextLevel();
		else {
			gameOverScreen();
			return;
		}
	}

	//collisions.......................................
	collisions();
	//--------------------------

	//erasing....................
	m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(), [this](auto & bullet)
	{
		if (!bullet->getIsAlive())
			return true;
		return false;
	}), m_bullets.end());


	m_powerUps.erase(std::remove_if(m_powerUps.begin(), m_powerUps.end(), [this](auto & powerUp)
	{
		if (!powerUp->getIsAlive())
			return true;
		return false;
	}), m_powerUps.end());


	m_enemies.erase(std::remove_if(m_enemies.begin(), m_enemies.end(), [](auto & enemy)
	{
		if (enemy->in_grave())
			return true;
		return false;
	}), m_enemies.end());

	//checking if hero died..............
	if (m_ship->getShipLife() <= 0)
		gameOverScreen();
}
//-----------------------------------------------------------------------------
void PlayingState::nextLevel()
{
	m_bullets.clear();
	m_bullets.resize(0);
	m_level++;
	m_levelmanager.setNextLevel(m_level, m_enemies, m_powerUps);
}
//-----------------------------------------------------------------------------
void PlayingState::updateShip(sf::Event& event)
{
	static sf::Time totalShootTime = sf::seconds(0.f);
	static bool held = false;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (!held)  //will be true while space bar is held down
		{

			m_bullets.emplace_back(m_ship->shoot());
			held = true;
			shoot_clock.restart();
		}
		//if space is held and timer passed
		else if (shoot_clock.getElapsedTime().asSeconds() >= m_ship->getShootTime().asSeconds())
		{
			auto p = m_ship->shoot();
			if (p)
			{

				m_bullets.emplace_back(std::move(p));
			}
			shoot_clock.restart();
		}
	}
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
		held = false;
}
//-----------------------------------------------------------------------------
void PlayingState::updateInnerHealthBar()
{
	if (m_lives.size() > m_ship->getShipLife())
		m_lives.erase(m_lives.end() - 1);
	else if (m_lives.size() < m_ship->getShipLife())
	{
		int i = m_ship->getShipLife() - 1;
		m_lives.push_back(m_shipSprite);
		m_lives[i].setPosition(80 + m_healthBar.getGlobalBounds().width + (i * 50), WINDOW_SIZE.y - m_healthBar.getGlobalBounds().height + 10);
		m_lives[i].setScale(0.7f, 0.7f);
	}

	float p = m_ship->getHealthFromShip() / MAX_HEALTH;
	m_innerHealthBar.setScale((p)*1.5f, 1.5f);
}
//-----------------------------------------------------------------------------
void PlayingState::scrollBackground(sf::RenderWindow &window)
{
	m_game->m_window.draw(m_gameBackground);
	m_game->m_window.draw(m_gameBackground2);
	m_gameBackground.move(0.f, 0.06f);
	m_gameBackground2.move(0.f, 0.06f);

	if ((m_gameBackground.getPosition().y) > WINDOW_SIZE.y) //out of screen
	{
		m_gameBackground.setPosition(0, (m_gameBackground2.getPosition().y - m_gameBackground2.getTexture()->getSize().y));
		m_gameBackground2.setPosition(0, (m_gameBackground.getPosition().y + m_gameBackground.getTexture()->getSize().y));
	}
	if ((m_gameBackground2.getPosition().y > WINDOW_SIZE.y)) //out of screen
	{
		m_gameBackground2.setPosition(0, (m_gameBackground.getPosition().y - m_gameBackground.getTexture()->getSize().y));
		m_gameBackground.setPosition(0, (m_gameBackground2.getPosition().y + m_gameBackground2.getTexture()->getSize().y));
	}
}
//-----------------------------------------------------------------------------
void PlayingState::gameOverScreen()
{
	m_game->popState();
	m_game->pushState(std::make_shared<GameOverState>(this->m_game, m_ship->getScore()));
}
//-----------------------------------------------------------------------------
void PlayingState::draw()
{
	m_game->m_window.draw(m_gameBackground);
	m_game->m_window.draw(m_gameBackground2);

	for (int i = 0; i < m_enemies.size(); i++)
	{
		if (!m_enemies[i]->getIsAlive())
		{

			m_ship->addScore(m_enemies[i]->getScore());

			if (i == m_teleported_enemy)
				m_teleported_enemy = -1;
			if (!m_enemies[i]->in_grave())
				m_enemies[i]->destroyEnemy(m_game->m_window);
		}
		else
			m_enemies[i]->draw(m_game->m_window);
	}
	m_ship->draw(m_game->m_window);

	m_game->m_window.draw(m_healthBar);
	m_game->m_window.draw(m_innerHealthBar);

	for (auto& bullet : m_bullets)
		bullet->draw(m_game->m_window);

	for (auto& life : m_lives)
		m_game->m_window.draw(life);


	for (auto& powerup : m_powerUps)
		powerup->draw(m_game->m_window);

	m_game->m_window.draw(m_gameScore);
}
//-----------------------------------------------------------------------------
void PlayingState::update()
{
	for (auto & enemy : m_enemies)
	{
		if (!enemy->in_grave())
			enemy->getStrategy()->resumeClock();
	}

	scrollBackground(m_game->m_window);
	updateInnerHealthBar();

	if (Resources::get_instance().chrono.getElapsedTime().asSeconds() - updateTime.asSeconds() >= moveTime.asSeconds())
	{
		update(m_game->m_window);
		updateTime += moveTime;
	}
	m_gameScore.setString("Score: " + std::to_string(m_ship->getScore()));
}
//-----------------------------------------------------------------------------
void PlayingState::handleInput()
{
	sf::Event event;

	updateShip(event);  //getting users input outsize the poll event for smoother movement

	while (m_game->m_window.pollEvent(event))
	{
		switch (event.type)
		{
			/* Close the window */
		case sf::Event::Closed:
			m_game->m_window.close();
			break;
			//pause game
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				PauseGame();
				break;
			}
			break;
		case sf::Event::LostFocus:
			PauseGame();
			break;
		}
	}
}
//-----------------------------------------------------------------------------
void PlayingState::activateStart()
{
	Resources::get_instance().chrono.reset(true);
	updateTime = sf::Time::Zero;
	shoot_clock.restart();
}
//-----------------------------------------------------------------------------
void PlayingState::PauseGame()
{
	for (auto & enemy : m_enemies)
		enemy->getStrategy()->pauseClock();

	m_game->pushState(std::make_shared<PauseState>(this->m_game));
}
//-----------------------------------------------------------------------------
void PlayingState::moveAll()
{
	std::for_each(m_enemies.begin(), m_enemies.end(), [this](auto& enemy)
	{
		if (!enemy->in_grave())
			enemy->move(m_ship->getPosition());
	});

	for (auto &powerup : m_powerUps)
	{
		if (powerup->getIsActive())
			powerup->move();
	}

	for (auto &bullet : m_bullets)
		bullet->move();

	m_ship->move();
}
//-----------------------------------------------------------------------------
void PlayingState::alienShoot()
{
	if (m_enemies.size() > 0)
	{
		int index = rand() % (m_enemies.size());

		if (Resources::get_instance().chrono.getElapsedTime() - totalShootTime >= shootTime)
		{
			if (m_teleported_enemy != -1 && m_teleported_enemy < m_enemies.size())
			{
				if (m_enemies[m_teleported_enemy]->getIsAlive())
					m_bullets.emplace_back(std::move(m_enemies[m_teleported_enemy]->shoot()));
			}

			if (m_enemies[index]->getIsAlive())
				m_bullets.emplace_back(std::move(m_enemies[index]->shoot()));
			totalShootTime += shootTime;
		}
	}
}
//-----------------------------------------------------------------------------
void PlayingState::teleportAlien()
{
	int index = 0;
	int counter = 0;
	if (m_enemies.size() > 0)
	{
		while (true) {

			index = rand() % (m_enemies.size());
			if (m_enemies[index]->getIsAlive())
				break;
			else
				counter++;

			if(counter == m_enemies.size())
				break;
		}

		if (m_enemies[index]->getTurn() && m_enemies[index]->getIsAlive())  //he is dead
		{
			if (Resources::get_instance().chrono.getElapsedTime().asSeconds() >= TOD.asSeconds() + 5.f)
			{
				m_teleported_enemy = index;
				Resources::get_instance().play(MUSIC_ID::TELEPORT_M);
				m_enemies[index]->setMoveStrategy(std::make_unique<TeleportMove>(std::move(m_enemies[index]->getStrategy())));
				m_enemies[index]->setTurn(false);
				TOD = sf::seconds(0.f);
			}
		}
		else
			TOD = Resources::get_instance().chrono.getElapsedTime(); //last time alive (TOD)
	}
}
//-----------------------------------------------------------------------------
void PlayingState::activatePowerUp()
{
	if (m_powerUps.size() > 0)
	{
		if (Resources::get_instance().chrono.getElapsedTime() - totalpowerUpTime >= powerUpTime)
		{
			int index = rand() % (m_powerUps.size());
			m_powerUps[index]->setIsActive(true);
			totalpowerUpTime += (sf::seconds(15.f) + powerUpTime);
		}
	}
}
//-----------------------------------------------------------------------------
void PlayingState::collisions()
{
	for (auto &bullet : m_bullets)
	{
		for (auto & enemy : m_enemies)
		{
			if (isCollision(bullet->getRect(), enemy->getRect()) && bullet->isHeroBullet() && enemy->getIsAlive())
				processCollision(*bullet, *enemy);
		}
	}

	std::for_each(m_bullets.begin(), m_bullets.end(), [this](auto & bullet)
	{
		if (isCollision(bullet->getRect(), m_ship->getRect()) && (!bullet->isHeroBullet()))
			processCollision(*bullet, *m_ship);
	});

	std::for_each(m_powerUps.begin(), m_powerUps.end(), [this](auto & powerUp)
	{
		if (isCollision(powerUp->getRect(), m_ship->getRect()))
			processCollision(*powerUp, *m_ship);
	});
}