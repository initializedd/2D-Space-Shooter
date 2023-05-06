#ifndef WEAPON_H
#define WEAPON_H

#include "Texture.h"
#include "Projectile.h"
#include "Timer.h"
#include <string>
#include <vector>

enum EntityType;

class Weapon
{
private:
	EntityType												m_ownerType;
	std::string												m_name;
	int														m_damage;
	std::vector<Projectile>									m_projectiles;
	Timer													m_lastShot;

public:
	Weapon(EntityType ownerType);
	~Weapon();

	void shoot(Pair<int> leftProjectilePos, Pair<int> rightProjectilePos, unsigned int delay);

	void updateProjectiles();

	std::string& getName();
	std::vector<Projectile>& getProjectiles();
	int getDamage() const;
};

#endif // !WEAPON_H