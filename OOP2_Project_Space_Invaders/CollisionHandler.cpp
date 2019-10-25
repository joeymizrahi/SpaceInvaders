#include "CollisionHandler.h"
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "DefaultBullet.h"
#include "SimpleEnemyBullet.h"
#include "Ship.h"
#include "SimpleEnemy.h"
#include "SmartEnemy.h"
#include "WaveBulletPowerUp.h"
#include "ExtraLife.h"
#include "WaveBullet.h"
#include "ShieldPowerUp.h"
#include "Logger.h"
#include "BossEnemy.h"

namespace { // unnamed namespace — the standard way to make function "static"

			// primary collision-processing functions

	void shipBullet(Entity& spaceShip, Entity& bullet)
	{
		bullet.setAliveOrDead(false);
		Ship& ship = dynamic_cast<Ship&>(spaceShip);
		Bullet& bul = dynamic_cast<Bullet&>(bullet);
		ship.setHealthToShip(bul.getDamage());
		Logger::getInstance().addLog("Ship and Bullet collision!");
		
	}

	void shipEnemy(Entity& spaceShip, Entity& enemy)
	{
		Logger::getInstance().addLog("Ship and Enemy collision!");
	}
		

	void SimpleenemyBullet(Entity& enemy, Entity& bullet)
	{
		Enemy& e = dynamic_cast<Enemy&>(enemy);
		Bullet& b = dynamic_cast<Bullet&>(bullet);
		e.setHealthToEnemy(b.getDamage());
		bullet.setAliveOrDead(false);
		Logger::getInstance().addLog("Enemy and Bullet collision!");
	
	}

	void SmartenemyBullet(Entity& enemy, Entity& bullet)
	{
		Enemy& e = dynamic_cast<Enemy&>(enemy);
		Bullet& b = dynamic_cast<Bullet&>(bullet);
		e.setHealthToEnemy(b.getDamage());
		bullet.setAliveOrDead(false);
		Logger::getInstance().addLog("SmartEnemy and Bullet collision!");
	
	}

	void shipPowerUp(Entity& spaceShip, Entity& powerup)
	{
		Ship& ship = dynamic_cast<Ship&>(spaceShip);
		PowerUp& pUp = dynamic_cast<PowerUp&>(powerup);
		ship.addScore(pUp.getScore());
		powerup.setAliveOrDead(false);
		sf::Time newTime(sf::seconds(0.17f));
		ship.setShootTime(newTime);
		ship.setBullet(WAVE_BULLET_STRING);
		Resources::get_instance().play(MUSIC_ID::POWER_UP_M);
		Logger::getInstance().addLog("Ship and PowerUp collision!");
	
	}
	void enemyWaveBullet(Entity& enemy, Entity& wave)
	{
		Enemy& e = dynamic_cast<Enemy&>(enemy);
		Bullet& b = dynamic_cast<Bullet&>(wave);
		e.setHealthToEnemy(b.getDamage());
		Logger::getInstance().addLog("enemy and waveBullet collision!");
	}

	void ShipExtraLife(Entity& ship, Entity& extralife)
	{
		Ship& e = dynamic_cast<Ship&>(ship);
		PowerUp& b = dynamic_cast<PowerUp&>(extralife);
		e.addLife();
		e.addScore(b.getScore());
		extralife.setAliveOrDead(false);
		Resources::get_instance().play(MUSIC_ID::POWER_UP_M);
		Logger::getInstance().addLog("ship and extra life collision!");
	}

	void ShieldShip(Entity& shield, Entity& ship)
	{
		Ship& e = dynamic_cast<Ship&>(ship);
		PowerUp& b = dynamic_cast<PowerUp&>(shield);
		shield.setAliveOrDead(false);
		e.addScore(b.getScore());
		Resources::get_instance().play(MUSIC_ID::POWER_UP_M);
		e.setShield(true);
		Logger::getInstance().addLog("ship and shield collision!");
	}

	void BulletBoss(Entity& bullet, Entity& boss)
	{
		bullet.setAliveOrDead(false);
		Bullet& bull = dynamic_cast<Bullet&>(bullet);
		Enemy& b = dynamic_cast<Enemy&>(boss);
		b.setHealthToEnemy(bull.getDamage());
		Logger::getInstance().addLog("bullet and boss collision!");
	}

	void WaveBulletBoss(Entity& bullet, Entity& boss)
	{
		bullet.setAliveOrDead(false);
		Bullet& bull = dynamic_cast<Bullet&>(bullet);
		Enemy& b = dynamic_cast<Enemy&>(boss);
		b.setHealthToEnemy(bull.getDamage());
		Logger::getInstance().addLog("bullet and boss collision!");
	}

	// secondary collision-processing functions that just
	// implement symmetry: swap the parameters and call a
	// primary function
	void bulletShip(Entity& bullet, Entity& spaceShip)
	{
		shipBullet(spaceShip, bullet);
	}

	void enemyShip(Entity& enemy, Entity& spaceShip)
	{
		shipEnemy(spaceShip, enemy);
	}

	void BulletSimpleEnemy(Entity& spaceStation, Entity& simpleEnemy)
	{
		SimpleenemyBullet(simpleEnemy, spaceStation);
	}

	void BulletSmartenemy(Entity& spaceStation, Entity& smartEnemy)
	{
		SmartenemyBullet(smartEnemy, spaceStation);
	}

	void powerupShip(Entity& powerup, Entity& spaceShip)
	{
		shipPowerUp(spaceShip, powerup);
	}

	void waveBulletEnemy(Entity& wave, Entity& enemy)
	{
		enemyWaveBullet(enemy, wave);
	}

	void extraLifeShip(Entity& extraLife, Entity& ship)
	{
		ShipExtraLife(ship, extraLife);
	}

	void ShipShield(Entity& shield, Entity& ship)
	{
		ShieldShip(ship, shield);
	}

	void bossBullet(Entity& boss, Entity& bullet)
	{
		BulletBoss(bullet, boss);
	}

	void bossWaveBullet(Entity& boss, Entity& bullet)
	{
		WaveBulletBoss(bullet, boss);
	}

	using HitFunctionPtr = void(*)(Entity&, Entity&);
	using Key = std::pair<std::type_index, std::type_index>;
	using HitMap = std::map<Key, HitFunctionPtr>;

	HitMap initializeCollisionMap()
	{
		HitMap phm;
		phm[Key(typeid(Ship), typeid(SimpleEnemyBullet))] = &shipBullet;
		phm[Key(typeid(SimpleEnemyBullet), typeid(Ship))] = &bulletShip;
		phm[Key(typeid(Ship), typeid(SimpleEnemy))] = &shipEnemy;
		phm[Key(typeid(SimpleEnemy), typeid(Ship))] = &enemyShip;
		phm[Key(typeid(DefaultBullet), typeid(SimpleEnemy))] = &BulletSimpleEnemy;
		phm[Key(typeid(SimpleEnemy), typeid(DefaultBullet))] = &SimpleenemyBullet;
		phm[Key(typeid(SmartEnemy), typeid(DefaultBullet))] = &SmartenemyBullet;
		phm[Key(typeid(DefaultBullet), typeid(SmartEnemy))] = &BulletSmartenemy;
		phm[Key(typeid(Ship), typeid(WaveBulletPowerUp))] = &shipPowerUp;
		phm[Key(typeid(WaveBulletPowerUp), typeid(Ship))] = &powerupShip;
		phm[Key(typeid(WaveBullet), typeid(SimpleEnemy))] = &waveBulletEnemy;
		phm[Key(typeid(SimpleEnemy), typeid(WaveBullet))] = &enemyWaveBullet;
		phm[Key(typeid(WaveBullet), typeid(SmartEnemy))] = &waveBulletEnemy;
		phm[Key(typeid(SmartEnemy), typeid(WaveBullet))] = &enemyWaveBullet;
		phm[Key(typeid(Ship), typeid(ExtraLife))] = &ShipExtraLife;  
		phm[Key(typeid(ExtraLife), typeid(Ship))] = &extraLifeShip;  
		phm[Key(typeid(Ship), typeid(ShieldPowerUp))] = &ShipShield;  
		phm[Key(typeid(ShieldPowerUp), typeid(Ship))] = &ShieldShip; 
		phm[Key(typeid(DefaultBullet), typeid(BossEnemy))] = &BulletBoss; 
		phm[Key(typeid(WaveBullet), typeid(BossEnemy))] = &WaveBulletBoss;

		return phm;
	}

	//looks up a map value by the keys
	HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
	{
		static HitMap collisionMap = initializeCollisionMap();
		auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
		if (mapEntry == collisionMap.end())
		{
			return nullptr;
		}
		return mapEntry->second;
	}

} // end namespace

//sends to correct collsion function 
void processCollision(Entity& object1, Entity& object2)
{
	auto phf = lookup(typeid(object1), typeid(object2));
	if (!phf)
	{
		throw UnknownCollision(object1, object2);
	}
	phf(object1, object2);
}

//checks to objects if thee was collision
bool isCollision(const sf::FloatRect& obj1, const sf::FloatRect&obj2)
{
	return obj1.intersects(obj2);
}