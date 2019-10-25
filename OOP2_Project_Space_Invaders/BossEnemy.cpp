#include "BossEnemy.h"
#include "EnemyFactory.h"
#include "BossMove.h"
#include "BulletFactory.h"

//-----------------------------------------------------------------------------
BossEnemy::BossEnemy(const enemy_pkg &x)
{
	your_turn = false;
	m_Sprite.setTexture(Resources::get_instance().getGeneralTexture(GENERAL_TEXTURES::BOSS_SHEET_T));
	m_life = 700;
	pMoveStrategy = std::make_unique<BossMove>(std::make_pair(sf::Vector2f{ 0, 0 }, sf::Vector2f{ WINDOW_SIZE.x, 600 }));
	maxY = x.yLimit;
	m_enemyScore = 500;
	m_Sprite.setOrigin(m_Sprite.getGlobalBounds().width / 2, m_Sprite.getGlobalBounds().height / 2);
	m_Sprite.setPosition(WINDOW_SIZE.x / 2, 200);
	Resources::get_instance().play(MUSIC_ID::BOSS_M);
}
//-----------------------------------------------------------------------------
void BossEnemy::move(sf::Vector2f shipPos)
{
	pMoveStrategy->move(*this, shipPos);
}
//-----------------------------------------------------------------------------
std::unique_ptr<Bullet> BossEnemy::shoot()const
{
	struct bullet_pkg shipBullet;
	shipBullet.initialPos = { m_Sprite.getPosition().x + 4  ,m_Sprite.getPosition().y + m_Sprite.getGlobalBounds().height / 2 - 230 };
	shipBullet.heroBullet = false;
	shipBullet.driection = { 0,1 };
	shipBullet.damage = -25;
	return m_bulletFactory_ptr->create("simple enemy bullet", shipBullet);
}
//-----------------------------------------------------------------------------
 sf::FloatRect BossEnemy::getRect() {  
	sf::FloatRect  newRect = m_Sprite.getGlobalBounds();
	newRect.left += 10.f;
	newRect.top += 10.f;
	newRect.height -= 60.f;
	newRect.width -= 30.f;
	return newRect;
}
//-----------------------------------------------------------------------------
void BossEnemy::draw(sf::RenderWindow & window)
{
	static float SpawnTime = Resources::get_instance().chrono.getElapsedTime().asSeconds();
	auto t = SpawnTime;
	auto t2 = Resources::get_instance().chrono.getElapsedTime().asSeconds();
	m_Sprite.setTextureRect(sf::IntRect((m_bossFrame % 11) * 297, 0, 297, 333));
	m_Sprite.setOrigin(m_Sprite.getGlobalBounds().width / 2, m_Sprite.getGlobalBounds().height / 2);
	m_Sprite.setPosition(m_Sprite.getPosition());
	window.draw(m_Sprite);

	if (SpawnTime + ((m_bossFrame)*0.1f) <= Resources::get_instance().chrono.getElapsedTime().asSeconds())
		m_bossFrame++;
}
//-----------------------------------------------------------------------------
//registering the entity to map
bool BossEnemy::m_registerit = EnemyFactory::registerit(ENEMY_CHARS::BOSS_ENEMY_C,
	[](const enemy_pkg& x) -> std::unique_ptr<Enemy> { return std::make_unique<BossEnemy>(x); });