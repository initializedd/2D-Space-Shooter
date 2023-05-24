#include "Entity.h"
#include "Globals.h"
#include "Constants.h"

Entity::Entity()
	: m_ship{}
	, m_type{}
	, m_id{}
	, m_textureRotation{}
	, m_direction{}
	, m_width{}
	, m_height{}
	, m_currentExhaustClip{}
	, m_currentDeathClip{}
	, m_pos{}
	, m_vel{}
	, m_leftCannonPos{}
	, m_rightCannonPos{}
	, m_health{}
	, m_particle{}
	, m_explosionFrames{}
	, m_flameFrames{}
	, m_weapon{ m_type }
	, m_canShoot{}
{
}

Entity::~Entity()
{
}

void Entity::move(double dt)
{
	// Update X position based on its X velocity
	m_pos.x += m_vel.x * dt;
	setColliders();

	// Check if outside screen boundary X
	checkScreenBoundaryX();

	// Check for collision on X axis
	if (checkCollisionPosX(gEnts))
	{
		setColliders();
	}

	// Update Y position based on its Y velocity
	m_pos.y += m_vel.y * dt;
	setColliders();

	// Check if outside screen boundary Y
	checkScreenBoundaryY();

	// Check for collision on Y axis
	if (checkCollisionPosY(gEnts))
	{
		setColliders();
	}
}

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

		m_weapon.shoot(leftCollider, rightCollider, delay, m_direction);
	}
}

void Entity::handleEvent(SDL_Event& event)
{
}

void Entity::calculateVelocity(Vector2<float> direction, int speed)
{
	m_vel.x = direction.x * speed;
	m_vel.y = direction.y * speed;
}

void Entity::checkScreenBoundaryX()
{
	for (int i = 0; i < m_ship.getParts().size(); ++i)
	{
		SDL_Rect& collider = m_ship.getParts()[i].getCollider().getRect();

		// Check if outside of left screen boundary
		if (collider.x < 0.f)
		{
			m_pos.x += std::abs(collider.x);
			setColliders();

			if (m_type == ENEMY)
				calculateVelocity(Vector2<float>(1.f, 0.f), ENEMY_SPEED);
		}

		// Check if outside of right screen boundary
		if (collider.x + collider.w > SCREEN_WIDTH)
		{
			float difference = std::abs(collider.x - m_pos.x);
			m_pos.x = SCREEN_WIDTH - collider.w - difference;
			setColliders();

			if (m_type == ENEMY)
				calculateVelocity(Vector2<float>(-1.f, 0.f), ENEMY_SPEED);
		}
	}
}

void Entity::checkScreenBoundaryY()
{
	for (int i = 0; i < m_ship.getParts().size(); ++i)
	{
		SDL_Rect& collider = m_ship.getParts()[i].getCollider().getRect();

		// Check if outside of top screen boundary
		if (collider.y < 0.f)
		{
			m_pos.y += std::abs(collider.y);

			setColliders();
		}

		// Check if outside of bottom screen boundary
		if (collider.y + collider.h > SCREEN_HEIGHT)
		{
			float difference = std::abs(collider.y - m_pos.y);
			m_pos.y = SCREEN_HEIGHT - collider.h - difference;

			setColliders();
		}
	}
}

bool Entity::checkCollisionPosX(std::vector<Entity*>& ents)
{
	for (int i = 0; i < ents.size(); ++i)
	{
		m_canShoot = true;

		if (this == ents[i])
			continue;

		for (int j = 0; j < m_ship.getParts().size(); ++j)
		{
			SDL_Rect thisCollider{ m_ship.getParts()[j].getCollider().getRect() };

			for (int k = 0; k < ents[i]->getShip().getParts().size(); ++k)
			{
				SDL_Rect entCollider{ ents[i]->getShip().getParts()[k].getCollider().getRect() };

				if (SDL_HasIntersection(&thisCollider, &entCollider))
				{
					if (m_type == ents[i]->m_type)
					{
						m_canShoot = false;
						return true;
					}

					if (m_pos.x <= ents[i]->getPos().x)
						m_pos.x = (ents[i]->getPos().x - (ents[i]->getPos().x - entCollider.x)) - ((thisCollider.x - m_pos.x) + thisCollider.w);

					if (m_pos.x > ents[i]->getPos().x)
						m_pos.x = (entCollider.x + entCollider.w) - (thisCollider.x - m_pos.x);

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

		for (int j = 0; j < m_ship.getParts().size(); ++j)
		{
			SDL_Rect thisCollider{ m_ship.getParts()[j].getCollider().getRect() };

			for (int k = 0; k < ents[i]->getShip().getParts().size(); ++k)
			{
				SDL_Rect entCollider{ ents[i]->getShip().getParts()[k].getCollider().getRect() };

				if (SDL_HasIntersection(&thisCollider, &entCollider))
				{
					if (m_pos.y <= ents[i]->getPos().y)
						m_pos.y = (ents[i]->getPos().y - (ents[i]->getPos().y - entCollider.y)) - ((thisCollider.y - m_pos.y) + thisCollider.h);

					if (m_pos.y > ents[i]->getPos().y)
						m_pos.y = (entCollider.y + entCollider.h) - (thisCollider.y - m_pos.y);

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

bool Entity::deathAnimation(double dt)
{
	if (m_explosionFrames / 2 <= 12)
	{
		m_currentDeathClip = &gExplosionParticle.getClips()[m_explosionFrames / 2];
		++m_explosionFrames;

		return false;
	}

	return true;
}

void Entity::exhaustAnimation(double dt)
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
	double textureRadians = m_textureRotation * (M_PI / 180.0);

	// Calculate the cosine and sine values of the texture's rotation angle
	double cosAngle = cos(textureRadians);
	double sinAngle = sin(textureRadians);

	// Calculate the centre coordinates of the rotated texture
	double textureCentreX = m_ship.getTexture().getWidth() / 2.0;
	double textureCentreY = m_ship.getTexture().getHeight() / 2.0;

	for (int i = 0; i < m_ship.getParts().size(); ++i)
	{
		// Calculate the centre coordinates of the collider
		double colliderCentreX = m_ship.getParts()[i].getCollider().getRect().w / 2.0;
		double colliderCentreY = m_ship.getParts()[i].getCollider().getRect().h / 2.0;

		// Translate the collider's centre to the texture's coordinate system
		double translatedX = m_ship.getParts()[i].getOffset().x + colliderCentreX - textureCentreX;
		double translatedY = m_ship.getParts()[i].getOffset().y + colliderCentreY - textureCentreY;

		// Rotate the collider's positions relative to the texture's rotation
		double rotatedX = translatedX * cosAngle - translatedY * sinAngle;
		double rotatedY = translatedX * sinAngle + translatedY * cosAngle;

		// Translate the rotated collider's positions back to the original coordinate system
		m_ship.getParts()[i].getCollider().getRect().x = static_cast<int>(rotatedX + textureCentreX - colliderCentreX + m_pos.x);
		m_ship.getParts()[i].getCollider().getRect().y = static_cast<int>(rotatedY + textureCentreY - colliderCentreY + m_pos.y);
	}
}