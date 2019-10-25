#pragma once
#include "PowerUp.h"

class ShieldPowerUp : public PowerUp
{
public:
	ShieldPowerUp(const powerUp_pkg& pkg);
	~ShieldPowerUp() = default;

private:
	static bool m_registerit;
};