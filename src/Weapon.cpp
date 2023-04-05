#include "Weapon.h"

Weapon::Weapon()
	: m_name{}
	, m_damage{}
	, m_projectile{}
{
}

Weapon::~Weapon()
{
	
}

void Weapon::shoot()
{
	
}

Projectile& Weapon::getProjectile()
{
	return m_projectile;
}

std::string& Weapon::getName()
{
	return m_name;
}

int Weapon::getDamage() const
{
	return m_damage;
}