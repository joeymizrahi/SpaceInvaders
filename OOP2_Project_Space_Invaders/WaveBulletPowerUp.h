#pragma once
#include "PowerUp.h"

class WaveBulletPowerUp : public PowerUp
{
public:
	WaveBulletPowerUp(const powerUp_pkg& x);
	~WaveBulletPowerUp() = default;
private:
	static bool m_registerit;
};