#pragma once
#include "PowerUp.h"

class PowerUpFactory
{
public:
	PowerUpFactory() = default;
	~PowerUpFactory() = default;

	static std::unique_ptr<PowerUp> create(const POWER_UP_CHARS&, const powerUp_pkg& x);
	static bool registerit(const POWER_UP_CHARS& name, std::unique_ptr<PowerUp>(*)(const powerUp_pkg& x));
	static std::map< POWER_UP_CHARS, std::unique_ptr<PowerUp>(*)(const powerUp_pkg&)>& getMap();
};