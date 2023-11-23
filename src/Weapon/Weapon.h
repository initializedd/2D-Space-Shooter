#ifndef WEAPON_H
#define WEAPON_H

#include "../Resource/Texture/Texture.h"
#include "../Weapon/Projectile/Projectile.h"
#include <string>
#include <vector>

enum EntityType : int;

class Weapon
{
private:
	EntityType												m_ownerType;
	std::string												m_name;
	int														m_damage;
	std::vector<Projectile>									m_projectiles;
	Vector2<float>											m_weaponDirection;

public:
	Weapon(EntityType ownerType, Vector2<float> weaponDirection);

	void shoot(Pair<int> leftProjectilePos, Pair<int> rightProjectilePos);

	void updateProjectiles(double dt);
	void renderProjectiles();

	std::string& getName();
	std::vector<Projectile>& getProjectiles();
	int getDamage() const;
};

#endif // !WEAPON_H
