#include "Entity.h"
#include "Globals.h"
#include "Constants.h"

Entity::Entity()
	: m_ship{}
	, m_type{}
	, m_textureRotation{}
	, m_direction{}
	, m_speed{}
	, m_width{}
	, m_height{}
	, m_currentExhaustClip{}
	, m_currentDeathClip{}
	, m_pos{}
	, m_movement{}
	, m_leftCannonPos{}
	, m_rightCannonPos{}
	, m_health{}
	, m_shield{}
	, m_particle{}
	, m_explosionFrames{}
	, m_flameFrames{}
	, m_weapon{ m_type, Vector2<float>(0, 0) }
	, m_canShoot{}
{
}

void Entity::move(double dt)
{
	m_movement.calculateVelocity(m_direction, m_speed);
	m_movement.move(m_pos, dt);

	checkScreenBoundary();
	checkCollision(gEnts);
}

//void Entity::move(double dt)
//{
//	// Update X position based on its X velocity
//	m_pos.x += m_vel.x * dt;
//	setColliders();
//
//	// Check if outside screen boundary X
//	checkScreenBoundaryX();
//
//	// Check for collision on X axis
//	if (checkCollisionPosX(gEnts))
//	{
//		setColliders();
//	}
//
//	// Update Y position based on its Y velocity
//	m_pos.y += m_vel.y * dt;
//	setColliders();
//
//	// Check if outside screen boundary Y
//	checkScreenBoundaryY();
//
//	// Check for collision on Y axis
//	if (checkCollisionPosY(gEnts))
//	{
//		setColliders();
//	}
//}

void Entity::shoot(int delay)
{
	if (!isDead())
	{
		Pair<int> leftCollider{};
		Pair<int> rightCollider{};

		for (int i = 0; i < m_ship.getParts().size(); ++i)
		{
			ShipPart& part = m_ship.getParts()[i];
			if (part.getPartType() == LEFT_WEAPON)
			{
				leftCollider.x = (m_ship.getParts()[i].getCollider().getRect().x) - (gLeftProjectileHitBox.x - (std::round(m_ship.getParts()[i].getCollider().getRect().w / 2) - (gLeftProjectileHitBox.w / 2)));	// Centre the projectile
				leftCollider.y = m_ship.getParts()[i].getCollider().getRect().y;
			}
			else if (part.getPartType() == RIGHT_WEAPON)
			{
				rightCollider.x = (m_ship.getParts()[i].getCollider().getRect().x) - (gRightProjectileHitBox.x - (std::round(m_ship.getParts()[i].getCollider().getRect().w / 2) - (gRightProjectileHitBox.w / 2))); // Centre the projectile;
				rightCollider.y = m_ship.getParts()[i].getCollider().getRect().y;
			}
		}

		m_weapon.shoot(leftCollider, rightCollider, delay);
	}
}

void Entity::handleEvent(SDL_Event& event)
{
}

void Entity::checkScreenBoundary()
{
	for (int i = 0; i < m_ship.getParts().size(); ++i)
	{
		Collider& collider = m_ship.getParts()[i].getCollider();

		if (collider.handleScreenCollision(m_pos, m_textureRotation))
			if (m_type == ENEMY)
				m_direction.x = -m_direction.x;
	}
}

bool Entity::checkCollision(std::vector<Entity*>& ents)
{
	for (int i = 0; i < ents.size(); ++i)
	{
		m_canShoot = true;

		if (this == ents[i])
			continue;

		for (int j = 0; j < m_ship.getParts().size(); ++j)
		{
			Collider& thisCollider{ m_ship.getParts()[j].getCollider() };

			for (int k = 0; k < ents[i]->getShip().getParts().size(); ++k)
			{
				Collider& entCollider{ ents[i]->getShip().getParts()[k].getCollider() };

				if (thisCollider.intersects(entCollider))
				{
					if (m_type == ents[i]->m_type)
					{
						m_canShoot = false;
						return true;
					}

					thisCollider.handleCollision(m_pos, ents[i]->getPos(), entCollider, m_textureRotation);

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
	if (!isDead())
	{
		for (int i = 0; i < m_ship.getParts().size(); ++i)
		{
			SDL_RenderDrawRect(gWindow.getRenderer(), &m_ship.getParts()[i].getCollider().getRect());
		}
	}
}
#endif

bool Entity::deathAnimation()
{
	if (m_explosionFrames / 2 <= 12)
	{
		m_currentDeathClip = &gExplosionParticle.getClips()[m_explosionFrames / 2];
		++m_explosionFrames;

		return false;
	}

	return true;
}

void Entity::exhaustAnimation()
{
	m_currentExhaustClip = &gExhaustParticle.getClips()[m_flameFrames / 3];

	++m_flameFrames;
	if (m_flameFrames / 3 >= 6)
	{
		m_flameFrames = 0;
	}
}

void Entity::renderDeathAnimation()
{
	int explosionPosX = (m_pos.x + m_ship.getTexture().getWidth() / 2) - gExplosionParticle.getTexture().getWidth() / 2;
	int explosionPosY = (m_pos.y + m_ship.getTexture().getHeight() / 2) - gExplosionParticle.getTexture().getHeight() / 2;

	gExplosionParticle.getTexture().render(explosionPosX, explosionPosY, m_currentDeathClip, gExplosionParticle.getTexture().getWidth(), gExplosionParticle.getTexture().getHeight());
}

void Entity::reduceHealth(int damage)
{
	if (m_shield > 0)
	{
		m_shield -= damage;

		if (m_shield < 0)
		{
			int excessDamage = std::abs(m_shield);
			m_health -= excessDamage;
		}
	}
	else
		m_health -= damage;
}

bool Entity::isDead()
{
	return m_health <= 0;
}

Ship& Entity::getShip()
{
	return m_ship;
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

Vector2<float> Entity::getPos() const
{
	return m_pos;
}

void Entity::setColliders()
{
	for (int i = 0; i < m_ship.getParts().size(); ++i)
	{
		Collider& collider = m_ship.getParts()[i].getCollider();
		collider.setColliders(m_pos, m_textureRotation);
	}
}