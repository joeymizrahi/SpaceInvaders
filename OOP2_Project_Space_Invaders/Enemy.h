#pragma once
#include "Weaponable.h"
#include "MoveStrategy.h"

class Bullet;

class Enemy : public Weaponable
{
public:
	Enemy();
	virtual ~Enemy() = default;;
	virtual void setHealthToEnemy(float d);
	virtual void destroyEnemy(sf::RenderWindow&);
	virtual void setMoveStrategy(std::unique_ptr<MoveStrategy>) = 0;
	virtual bool in_grave()const { return m_burried; }
	void setPosition(const sf::Vector2f & start_pos)override;
	void setTurn(const bool turn) { your_turn = turn; }
	void draw(sf::RenderWindow&) override;
	void setTeleport(const bool isIt) { is_teleporting = isIt; }
	bool getTurn()const { return your_turn; }
	virtual std::unique_ptr<Bullet> shoot() const = 0;
	sf::Sprite& getSprite() { return m_Sprite; }
	std::unique_ptr<MoveStrategy>& getStrategy() { return pMoveStrategy; }
protected:
	int m_explosionFrame = 0;
	float m_life;  //maybe add to weaponable
	float maxY;
	bool m_burried = false;
	bool is_teleporting = false;
	static bool your_turn;
	sf::Sprite m_explosion;
	sf::Sprite m_teleport_sprite;
	sf::Time TOD = sf::seconds(0.f);
	std::unique_ptr<MoveStrategy> pMoveStrategy;
	unsigned m_enemyScore;
};