#include "Entity.h"
#include "Globals.h"
#include "Constants.h"

Entity::Entity()
	: m_type{}
	, m_id{}
	, m_texture{}
	, m_width{}
	, m_height{}
	, m_pos{}
	, m_vel{}
	, m_leftProjectilePos{}
	, m_rightProjectilePos{}
	, m_colliders{}
	, m_health{}
	, m_particle{}
	, m_explosionFrames{}
	, m_weapon{ m_type }
	, m_canShoot{}
{
}

Entity::~Entity()
{
}

void Entity::move()
{
	// Update X position based on its X velocity
	m_pos.x += m_vel.x;
	setColliders();

	// Check if outside of left screen boundary
	if (m_pos.x <= 0)
	{
		m_pos.x = 0;
		setColliders();

		if (m_type == ENEMY)
			m_vel.x = ENEMY_VEL;
	}
	// Check if outside of right screen boundary
	else if (m_pos.x + m_texture.getWidth() >= SCREEN_WIDTH)
	{
		m_pos.x = SCREEN_WIDTH - m_texture.getWidth();
		setColliders();

		if (m_type == ENEMY)
			m_vel.x = -ENEMY_VEL;
	}
	// Check for collision on X axis
	else if (checkCollisionPosX(gEnts))
	{
		setColliders();
	}

	// Update Y position based on its Y velocity
	m_pos.y += m_vel.y;
	setColliders();

	// Check if outside of top screen boundary
	if (m_pos.y <= 0)
	{
		m_pos.y = 0;
		setColliders();
	}
	// Check if outside of bottom screen boundary
	else if (m_pos.y + m_texture.getHeight() + m_particle.getTexture().getHeight() >= SCREEN_HEIGHT)
	{
		m_pos.y = SCREEN_HEIGHT - m_texture.getHeight() - m_particle.getTexture().getHeight();
		setColliders();
	}
	// Check for collision on Y axis
	else if (checkCollisionPosY(gEnts))
	{
		setColliders();
	}
}

void Entity::handleEvent(SDL_Event& event)
{
}

bool Entity::checkCollisionPosX(std::vector<Entity*>& ents)
{
	for (int i = 0; i < ents.size(); ++i)
	{
		m_canShoot = true;

		if (this == ents[i])
			continue;

		for (int j = 0; j < m_colliders.size(); ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				if (SDL_HasIntersection(&m_colliders[j], &ents[i]->getColliders()[k]))
				{
					if (m_type == ents[i]->m_type)
					{
						m_canShoot = false;
						return true;
					}

					if (m_pos.x <= ents[i]->getPosX())
						m_pos.x = (ents[i]->getPosX() - (ents[i]->getPosX() - ents[i]->getColliders()[k].x)) - ((m_colliders[j].x - m_pos.x) + m_colliders[j].w);

					if (m_pos.x > ents[i]->getPosX())
						m_pos.x = (ents[i]->getColliders()[k].x + ents[i]->getColliders()[k].w) - (m_colliders[j].x - m_pos.x);

					return true;
				}
			}
		}
	}

	return false;
}

bool Entity::checkCollisionPosY(std::vector<Entity*>& ents)
{
	for (int i = 0; i < ents.size(); ++i)
	{
		if (this == ents[i] || m_type == ents[i]->m_type)
			continue;

		for (int j = 0; j < m_colliders.size(); ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				if (SDL_HasIntersection(&m_colliders[j], &ents[i]->getColliders()[k]))
				{
					if (m_pos.y <= ents[i]->getPosY())
						m_pos.y = (ents[i]->getPosY() - (ents[i]->getPosY() - ents[i]->getColliders()[k].y)) - ((m_colliders[j].y - m_pos.y) + m_colliders[j].h);

					if (m_pos.y > ents[i]->getPosY())
						m_pos.y = (ents[i]->getColliders()[k].y + ents[i]->getColliders()[k].h) - (m_colliders[j].y - m_pos.y);

					return true;
				}
			}
		}
	}

	return false;
}

#if defined(_DEBUG)
void Entity::debug()
{
	for (int i = 0; i < m_colliders.size(); ++i)
	{
		SDL_RenderDrawRect(gWindow.getRenderer(), &m_colliders[i]);
	}
}
#endif

void Entity::shoot(int delay)
{
	if (m_canShoot)
		m_weapon.shoot(m_leftProjectilePos, m_rightProjectilePos, delay);
}

int Entity::deathAnimation()
{
	SDL_Rect* currentClip = &gExplosionParticle.getClips()[m_explosionFrames / 2];

	int explosionPosX = (m_pos.x + m_texture.getWidth() / 2) - gExplosionParticle.getTexture().getWidth() / 2;
	int explosionPosY = (m_pos.y + m_texture.getHeight() / 2) - gExplosionParticle.getTexture().getHeight() / 2;

	gExplosionParticle.getTexture().render(explosionPosX, explosionPosY, currentClip, gExplosionParticle.getTexture().getWidth(), gExplosionParticle.getTexture().getHeight());

	++m_explosionFrames;
	return m_explosionFrames;
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

int Entity::getType() const
{
	return m_type;
}

int Entity::getHealth() const
{
	return m_health;
}

int Entity::getPosX() const
{
	return m_pos.x;
}

int Entity::getPosY() const
{
	return m_pos.y;
}