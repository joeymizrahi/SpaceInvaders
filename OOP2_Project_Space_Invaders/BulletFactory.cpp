#include "BulletFactory.h"

std::map<std::string, std::unique_ptr<Bullet>(*)(const bullet_pkg&)> BulletFactory::m_bullets;

//-----------------------------------------------------------------------------
std::unique_ptr<Bullet> BulletFactory::create(const std::string& name,const bullet_pkg& x)
{

	auto it = m_bullets.find(name);
	if (it == m_bullets.end())
		return nullptr;
   	return it->second(x);
}
//-----------------------------------------------------------------------------
bool BulletFactory::registerit(const std::string& name, std::unique_ptr<Bullet>(*e)(const bullet_pkg&))
{
	m_bullets.emplace(name, e);
	return true;
}