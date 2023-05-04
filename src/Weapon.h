#ifndef WEAPON_H
#define WEAPON_H

#include "Texture.h"
#include "Projectile.h"
#include "Timer.h"
#include <string>
#include <vector>

class Weapon
{
private:
	std::string												m_name;
	int														m_damage;
	std::vector<Projectile>									m_projectiles;
	Timer													m_lastShot;

public:
	Weapon();
	~Weapon();

	void shoot(Pair<int> leftCannonPos, Pair<int> rightCannonPos, unsigned int delay);

	void updatePlayerProjectiles();
	void updateEnemyProjectiles();

	std::string& getName();
	int getDamage() const;
};

#endif // !WEAPON_H