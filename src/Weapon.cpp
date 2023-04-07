#include "Weapon.h"
#include "Globals.h"
#include "Constants.h"

Weapon::Weapon()
	: m_name{}
	, m_damage{}
	, m_projectiles{}
{
}

Weapon::~Weapon()
{
	for (auto& projectile : m_projectiles)
	{
		projectile.getTexture().free();
	}
}

void Weapon::shoot()
{
	Projectile projectile{};
	projectile.setPosX(gPlayer.getPosX());
	projectile.setPosY(gPlayer.getPosY());
	projectile.setTexture(gProjectileTexture);

	m_projectiles.push_back(projectile);

	//m_projectiles.at(0).setTexture(gProjectileTexture);
}

void Weapon::updateProjectiles()
{
	for (auto& projectile : m_projectiles)
	{
		projectile.getTexture().render(projectile.getPosX(), projectile.getPosY(), &gRedLaserClip, 90);
		projectile.move();
	}
}

std::string& Weapon::getName()
{
	return m_name;
}

int Weapon::getDamage() const
{
	return m_damage;
}