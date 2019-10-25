#pragma once
#include "Macros.h"
#include "Bullet.h"

class BulletFactory
{
public:
	static std::unique_ptr<Bullet> create(const std::string& name, const bullet_pkg&);
	static bool registerit(const std::string& name, std::unique_ptr<Bullet>(*)(const bullet_pkg&));

private:
	static std::map<std::string, std::unique_ptr<Bullet>(*)(const bullet_pkg&)> m_bullets;
};