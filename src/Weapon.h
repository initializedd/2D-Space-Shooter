#ifndef WEAPON_H
#define WEAPON_H

#include "Texture.h"
#include "Projectile.h"
#include <string>
#include <vector>

class Weapon
{
private:
	std::string						m_name;
	int								m_damage;
	std::vector<Projectile>			m_projectiles;

public:
	Weapon();
	~Weapon();

	void shoot();

	void updateProjectiles();

	std::string& getName();
	int getDamage() const;
};

#endif // !WEAPON_H