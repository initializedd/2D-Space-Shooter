#include "Weapon.h"

Weapon::Weapon()
	: m_name{}
	, m_damage{}
	, m_texture{}
{
}

Weapon::~Weapon()
{
	m_texture.free();
}

void Weapon::shoot()
{

}

const std::string& Weapon::getName() const
{
	return m_name;
}

const int Weapon::getDamage() const
{
	return m_damage;
}

const Texture& Weapon::getTexture() const
{
	return m_texture;
}