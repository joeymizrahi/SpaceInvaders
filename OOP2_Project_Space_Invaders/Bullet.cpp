#include "Bullet.h"
#include "BulletFactory.h"

//-----------------------------------------------------------------------------
inline void Bullet::setDirection(const sf::Vector2f & new_dir) { m_direction = new_dir; }
//-----------------------------------------------------------------------------
void Bullet::setOwner(bool heroBullet) { m_heroBullet = heroBullet; }
