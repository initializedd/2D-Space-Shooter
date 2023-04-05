#ifndef WEAPON_H
#define WEAPON_H

#include "Texture.h"
#include "Projectile.h"
#include <string>

class Weapon
{
private:
	std::string		m_name;
	int				m_damage;
	Projectile      m_projectile;

public:
	Weapon();
	~Weapon();

	void shoot();

	Projectile& getProjectile();
	std::string& getName();
	int getDamage() const;
};

#endif // !WEAPON_H