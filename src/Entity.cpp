#include "Entity.h"
#include "Constants.h"

Entity::Entity()
	: m_texture{}
	, m_width{}
	, m_height{}
	, m_pos{}
	, m_vel{}
	, m_colliders{}
	, m_health{}
	, m_particle{}
	, m_weapon{}
{
}

Entity::~Entity()
{
}

void Entity::move()
{
	// Update X position based on its X velocity
	m_pos.x += m_vel.x;

	// Check if outside of left screen boundary
	if (m_pos.x <= 0)
	{
		m_pos.x = 0;
	}
	// Check if outside of right screen boundary
	else if (m_pos.x + m_texture.getWidth() >= SCREEN_WIDTH)
	{
		m_pos.x = SCREEN_WIDTH - m_texture.getWidth();
	}

	// Update Y position based on its Y velocity
	m_pos.y += m_vel.y;

	// Check if outside of top screen boundary
	if (m_pos.y <= 0)
	{
		m_pos.y = 0;
	}
	// Check if outside of bottom screen boundary
	else if (m_pos.y + m_texture.getHeight() + m_particle.getTexture().getHeight() >= SCREEN_HEIGHT)
	{
		m_pos.y = SCREEN_HEIGHT - m_texture.getHeight() - m_particle.getTexture().getHeight();
	}
}

void Entity::shoot()
{
	m_weapon.shoot();
}

void Entity::reduceHealth(int damage)
{
	m_health -= damage;
}

bool Entity::isDead()
{
	return m_health <= 0;
}

std::vector<SDL_Rect>& Entity::getColliders()
{
	return m_colliders;
}

Texture& Entity::getTexture()
{
	return m_texture;
}

Particle& Entity::getParticle()
{
	return m_particle;
}

Weapon& Entity::getWeapon()
{
	return m_weapon;
}

int Entity::getPosX() const
{
	return m_pos.x;
}

int Entity::getPosY() const
{
	return m_pos.y;
}