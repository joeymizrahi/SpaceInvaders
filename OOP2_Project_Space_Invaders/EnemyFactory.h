#pragma once
#include "Enemy.h"

class EnemyFactory
{
public:
	EnemyFactory() = default;
	~EnemyFactory() = default;
	static std::unique_ptr<Enemy> create(const ENEMY_CHARS&, const enemy_pkg& x);
	static bool registerit(const ENEMY_CHARS& name, std::unique_ptr<Enemy>(*)(const enemy_pkg& x));
	static std::map< ENEMY_CHARS, std::unique_ptr<Enemy>(*)(const enemy_pkg&)>& getMap();
};
