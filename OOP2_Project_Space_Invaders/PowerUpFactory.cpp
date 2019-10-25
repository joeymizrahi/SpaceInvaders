#include "PowerUpFactory.h"
#include "Macros.h"

//-----------------------------------------------------------------------------
std::unique_ptr<PowerUp> PowerUpFactory::create(const POWER_UP_CHARS& name, const powerUp_pkg& x)
{
	auto it = getMap().find(name);
	if (it == getMap().end())
		return nullptr;
	return it->second(x);
}
//-----------------------------------------------------------------------------
bool PowerUpFactory::registerit(const POWER_UP_CHARS& name, std::unique_ptr<PowerUp>(*e)(const powerUp_pkg&))
{
	getMap().emplace(name, e);
	return true;
}
//-----------------------------------------------------------------------------
  std::map< POWER_UP_CHARS, std::unique_ptr<PowerUp>(*)(const powerUp_pkg&)>& PowerUpFactory::getMap()
{
	static std::map<POWER_UP_CHARS, std::unique_ptr<PowerUp>(*)(const powerUp_pkg&)> m_powerUps;
	return m_powerUps;
}