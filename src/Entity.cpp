#include "Entity.h"
#include "Common.h"
#include "Game.h"

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
	, m_sprite{}
	, m_explosionFrames{}
	, m_flameFrames{}
	, m_weapon{ m_type, Vector2<float>(0, 0) }
	, m_canShoot{}
	, m_lastShot{}
{
}

void Entity::move(double dt)
{
	m_movement.calculateVelocity(m_direction, m_speed);

	m_movement.move(m_pos, dt);
	createColliders();

	checkScreenBoundary();
	checkCollision(gEnts);
}

void Entity::shoot(int delay)
{
	if (!isDead())
	{
		if (!m_lastShot.isStarted())
		{
			m_lastShot.start();
		}
		else if (m_lastShot.getTicks() < delay)
		{
			return; // not enough time has passed
		}
		m_lastShot.start();

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

		m_weapon.shoot(leftCollider, rightCollider);
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

	createColliders();
}

void Entity::checkCollision(std::vector<std::unique_ptr<Entity>>& ents)
{
	for (int i = 0; i < ents.size(); ++i)
	{
		m_canShoot = true;

		if (this == ents[i].get())
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
						continue;
					}

					thisCollider.handleCollision(m_pos, ents[i]->getPos(), entCollider);
				}
			}
		}
	}

	createColliders();
}

#if defined(_DEBUG)
void Entity::debug()
{
	if (!isDead())
	{
		for (int i = 0; i < m_ship.getParts().size(); ++i)
		{
			SDL_SetRenderDrawColor(resourceManager.getRenderSystem().getWindow().getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
			SDL_RenderDrawRect(resourceManager.getRenderSystem().getWindow().getRenderer(), &m_ship.getParts()[i].getCollider().getRect());
		}
	}
}
#endif

bool Entity::deathAnimation()
{
	if (m_explosionFrames / 2 <= 12)
	{
		m_currentDeathClip = &resourceManager.getTextureSystem().findSprite("sprite_explosion")->getClips()[m_explosionFrames / 2];
		++m_explosionFrames;

		return false;
	}

	return true;
}

void Entity::exhaustAnimation()
{
	m_currentExhaustClip = &resourceManager.getTextureSystem().findSprite("sprite_fire")->getClips()[m_flameFrames / 3];

	++m_flameFrames;
	if (m_flameFrames / 3 >= 6)
	{
		m_flameFrames = 0;
	}
}

void Entity::renderDeathAnimation()
{
	if (m_currentDeathClip)
	{
		std::shared_ptr<Sprite> ship = resourceManager.getTextureSystem().findSprite("sprite_ships");
		std::shared_ptr<Sprite> explosion = resourceManager.getTextureSystem().findSprite("sprite_explosion");

		int explosionPosX = (m_pos.x + ship->getClips()[m_ship.getIndex()].w / 4) - m_currentDeathClip->w / 2;
		int explosionPosY = (m_pos.y + ship->getClips()[m_ship.getIndex()].h / 4) - m_currentDeathClip->h / 2;

		explosion->render(explosionPosX, explosionPosY, m_currentDeathClip->w, m_currentDeathClip->h, m_currentDeathClip);
	}
}

void Entity::reduceHealth(int damage)
{
	if (m_shield > 0)
	{
		m_shield -= damage;

		if (m_shield <= 0)
		{
			int excessDamage = std::abs(m_shield);
			m_health -= excessDamage;
			m_shield = 0;
			resourceManager.getSoundSystem().findSound("sfx_shield_destroy")->playChunk(-1, 0, 50);
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

Sprite& Entity::getSprite()
{
	return m_sprite;
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

void Entity::createColliders()
{
	for (int i = 0; i < m_ship.getParts().size(); ++i)
	{
		Collider& collider = m_ship.getParts()[i].getCollider();
		collider.createColliders(m_pos, m_textureRotation);
	}
}