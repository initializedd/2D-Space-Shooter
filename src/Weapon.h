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
	Vector2<float>											m_weaponDirection;
	Timer													m_lastShot;

public:
	Weapon(EntityType ownerType, Vector2<float> weaponDirection);

	void shoot(Pair<int> leftCannonPos, Pair<int> rightCannonPos, unsigned int delay);

	void updateProjectiles(double dt);
	void renderProjectiles();

	std::string& getName();
	std::vector<Projectile>& getProjectiles();
	int getDamage() const;
};

#endif // !WEAPON_H