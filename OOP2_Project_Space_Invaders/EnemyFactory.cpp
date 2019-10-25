#include "EnemyFactory.h"
#include "Macros.h"

//-----------------------------------------------------------------------------
std::unique_ptr<Enemy> EnemyFactory::create(const ENEMY_CHARS& name, const enemy_pkg& x)
{
	auto it = getMap().find(name);
	if (it == getMap().end())
		return nullptr;
	return it->second(x);
}
//-----------------------------------------------------------------------------
bool EnemyFactory::registerit(const ENEMY_CHARS& name, std::unique_ptr<Enemy>(*e)(const enemy_pkg&))
{
	getMap().emplace(name, e);
	return true;
}
//-----------------------------------------------------------------------------
std::map< ENEMY_CHARS, std::unique_ptr<Enemy>(*)(const enemy_pkg&)>& EnemyFactory::getMap()
{
	static std::map<ENEMY_CHARS, std::unique_ptr<Enemy>(*)(const enemy_pkg&)> m_powerUps;
	return m_powerUps;
}