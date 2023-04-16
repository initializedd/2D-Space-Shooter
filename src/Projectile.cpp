#include "Projectile.h"
#include "Globals.h"
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
	SDL_SetRenderDrawColor(gWindow.getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(gWindow.getRenderer(), &this->getCollider());

	SDL_SetRenderDrawColor(gWindow.getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(gWindow.getRenderer(), &box);

	// Check for collision
	return SDL_HasIntersection(&this->getCollider(), &box);
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

void Projectile::setCollider(SDL_Rect& box)
{
	m_collider.x = m_pos.x + box.x;
	m_collider.y = m_pos.y + box.y;
	m_collider.w = box.w;
	m_collider.h = box.h;
}