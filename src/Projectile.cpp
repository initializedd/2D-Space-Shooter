#include "Projectile.h"
#include "Constants.h"
#include <cstdio>

Projectile::Projectile()
	: m_pos{}
	, m_vel{}
	, m_texture{}
	, m_collider{}
{
}

Projectile::~Projectile()
{
}

void Projectile::move()
{
	m_pos.y -= LASER_VEL;
}

bool Projectile::checkCollision(SDL_Rect& box)
{
	SDL_Rect projectileBox;
	projectileBox.x = this->getPosX();
	projectileBox.y = this->getPosY();
	projectileBox.w = this->getPosX() + this->getTexture().getWidth();
	projectileBox.h = this->getPosY() + this->getTexture().getHeight();

	SDL_Rect enemyBox;
	enemyBox.x = box.x;
	enemyBox.y = box.y;
	enemyBox.w = box.x + box.w;
	enemyBox.h = box.y + box.h;

	// Check for collision
	return SDL_HasIntersection(&projectileBox, &enemyBox);
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

SDL_Rect& Projectile::getCollider()
{
	return m_collider;
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

void Projectile::setCollider()
{
	m_collider.x = m_pos.x;
	m_collider.y = m_pos.y;
	m_collider.w = m_pos.x + m_texture.getWidth();
	m_collider.h = m_pos.y + m_texture.getHeight();
}