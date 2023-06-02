#include "Projectile.h"
#include "Globals.h"
#include "Constants.h"
#include <cstdio>

Projectile::Projectile()
	: m_pos{}
	, m_direction{}
	, m_movement{}
	, m_collider{}
	, m_texture{}
	, m_type{}
	, m_damage{}
{
	m_damage = 50;
}

void Projectile::move(double dt)
{
	m_movement.calculateVelocity(m_direction, PROJECTILE_SPEED);
	m_movement.move(m_pos, dt);

	//m_pos.y += m_vel.y * dt;
}

bool Projectile::checkScreenBoundary()
{
	SDL_Rect screen(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// Checks if projectile is outside the screen
	if (!SDL_HasIntersection(&m_collider.getRect(), &screen))
	{
		return true;
	}

	return false;
}

bool Projectile::checkCollision(std::vector<Entity*>& ents, EntityType ownerType)
{
	for (int i = 0; i < ents.size(); ++i)
	{
		if (ownerType == ents[i]->getType())
			continue;

		for (int j = 0; j < ents[i]->getShip().getParts().size(); ++j)
		{
			// Check for collision
			if (m_collider.intersects(ents[i]->getShip().getParts()[j].getCollider()))
			{
				if (!ents[i]->isDead())
				{
					ents[i]->reduceHealth(m_damage);

					if (ents[i]->isDead())
					{
						gExplosionSound.playChunk(-1, 0, 10);
					}
				}

				return true;
			}
		}
	}

	return false;
}

void Projectile::createCollider()
{
	switch (m_type)
	{
		case LEFT_PROJECTILE:
			m_collider = { gLeftProjectileHitBox };
			break;

		case RIGHT_PROJECTILE:
			m_collider = { gRightProjectileHitBox };
			break;
	}
}

void Projectile::updateCollider()
{
	m_collider.setColliders(m_pos, 0.0);
}

void Projectile::render()
{
	switch (m_type)
	{
		case LEFT_PROJECTILE:
			gProjectileTexture.render(m_pos.x, m_pos.y, &gRedProjectileClip, gRedProjectileClip.w, gRedProjectileClip.h, 90);
			break;

		case RIGHT_PROJECTILE:
			gProjectileTexture.render(m_pos.x, m_pos.y, &gRedProjectileClip, gRedProjectileClip.w, gRedProjectileClip.h, 90, nullptr, SDL_FLIP_VERTICAL);
			break;
	}

	#if defined(_DEBUG)
	// Projectile Debug Info
	debug();
	#endif
}

void Projectile::debug()
{
	const SDL_Rect& rect = m_collider.getRect();

	std::stringstream pos;
	pos.str(std::to_string(rect.x) + ',' + std::to_string(rect.y));

	Texture projectilePos{};
	projectilePos.loadFromRenderedText(pos.str().c_str(), gFuturaFont, SDL_Color(0x00, 0xFF, 0x00, 0xFF));
	projectilePos.scale(45, 20);


	switch (m_type)
	{
		case LEFT_PROJECTILE:
			if (m_movement.getVel().y < 0)
				projectilePos.render(rect.x - projectilePos.getWidth() - 1, rect.y - projectilePos.getHeight());

			else if (m_movement.getVel().y > 0)
				projectilePos.render(rect.x + rect.w, rect.y - projectilePos.getHeight());
			break;

		case RIGHT_PROJECTILE:
			if (m_movement.getVel().y < 0)
				projectilePos.render(rect.x + rect.w, rect.y - projectilePos.getHeight());

			else if (m_movement.getVel().y > 0)
				projectilePos.render(rect.x - projectilePos.getWidth() - 1, rect.y - projectilePos.getHeight());
			break;
	}

	m_collider.drawCollider();
}

Vector2<float> Projectile::getPos() const
{
	return m_pos;
}

Texture& Projectile::getTexture()
{
	return m_texture;
}

ProjectileType Projectile::getType()
{
	return m_type;
}

void Projectile::setPos(Pair<int> pos)
{
	m_pos.x = pos.x;
	m_pos.y = pos.y;
}

void Projectile::setDirection(Vector2<float> direction)
{
	m_direction.x = direction.x;
	m_direction.y = direction.y;
}

void Projectile::setTexture(Texture& texture)
{
	m_texture = texture;
}

void Projectile::setType(ProjectileType type)
{
	m_type = type;
}