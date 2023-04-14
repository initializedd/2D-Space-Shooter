#include "Entity.h"

Entity::Entity(int x, int y)
	: m_texture{}
	, m_width{}
	, m_height{}
	, m_vel{}
	, m_health{}
	, m_particle{}
	, m_weapon{}
{
	m_pos.x = x;
	m_pos.y = y;
}

Entity::~Entity()
{
}

void Entity::move()
{

}

void Entity::shoot()
{
	m_weapon.shoot();
}

bool Entity::checkCollision(SDL_Rect& box)
{
	this->setCollider();

	return SDL_HasIntersection(&this->getCollider(), &box);
}

SDL_Rect& Entity::getCollider()
{
	return m_collider;
}


Texture& Entity::getTexture()
{
	return m_texture;
}

int Entity::getPosX() const
{
	return m_pos.x;
}

int Entity::getPosY() const
{
	return m_pos.y;
}

void Entity::setCollider()
{
	m_collider.x = m_pos.x;
	m_collider.y = m_pos.y;
	m_collider.w = m_texture.getWidth();
	m_collider.h = m_texture.getHeight();
}