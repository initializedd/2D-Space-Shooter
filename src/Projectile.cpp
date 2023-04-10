#include "Projectile.h"
#include "Constants.h"
#include <cstdio>

Projectile::Projectile()
	: m_pos{}
	, m_vel{}
	, m_texture{}
{
	printf("Projectile Created!\n");
}

Projectile::~Projectile()
{
	printf("Projectile Destroyed!\n");
}

void Projectile::move()
{
	m_pos.y -= LASER_VEL;
}

int Projectile::getPosX() const
{
	return m_pos.x;
}

int Projectile::getPosY() const
{
	return m_pos.y;
}

int Projectile::getVelX() const
{
	return m_vel.x;
}

int Projectile::getVelY() const
{
	return m_vel.y;
}

Texture& Projectile::getTexture()
{
	return m_texture;
}

void Projectile::setPosX(int x)
{
	m_pos.x = x;
}

void Projectile::setPosY(int y)
{
	m_pos.y = y;
}

void Projectile::setVelX(int x)
{
	m_vel.x = x;
}

void Projectile::setVelY(int y)
{
	m_vel.y = y;
}

void Projectile::setTexture(Texture& texture)
{
	m_texture = texture;
}