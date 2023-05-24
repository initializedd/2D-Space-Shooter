#include "Projectile.h"
#include "Globals.h"
#include "Constants.h"
#include <cstdio>

Projectile::Projectile()
	: m_pos{}
	, m_vel{}
	, m_texture{}
	, m_type{}
	, m_collider{}
	, m_damage{}
{
	m_damage = 50;
}

Projectile::~Projectile()
{
}

void Projectile::move(double dt)
{
	m_pos.y += m_vel.y * dt;
}

bool Projectile::checkScreenBoundary()
{
	SDL_Rect screen(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// Checks if projectile is outside the screen
	if (!SDL_HasIntersection(&m_collider, &screen))
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

		for ( int j = 0; j < ents[i]->getShip().getParts().size(); ++j)
		{
			// Check for collision
			if (SDL_HasIntersection(&m_collider, &ents[i]->getShip().getParts()[j].getCollider().getRect()))
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

void Projectile::updateCollider()
{
	switch(m_type)
	{
		case LEFT_PROJECTILE:
			m_collider.x = m_pos.x + gLeftProjectileHitBox.x;
			m_collider.y = m_pos.y + gLeftProjectileHitBox.y;
			m_collider.w = gLeftProjectileHitBox.w;
			m_collider.h = gLeftProjectileHitBox.h;
			break;

		case RIGHT_PROJECTILE:
			m_collider.x = m_pos.x + gRightProjectileHitBox.x;
			m_collider.y = m_pos.y + gRightProjectileHitBox.y;
			m_collider.w = gRightProjectileHitBox.w;
			m_collider.h = gRightProjectileHitBox.h;
			break;
	}
}

void Projectile::calculateVelocity(Vector2<float> direction, int speed)
{
	m_vel.x = direction.x * speed;
	m_vel.y = direction.y * speed;
}

void Projectile::render()
{
	switch(m_type)
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

void Projectile::drawCollision()
{
	SDL_SetRenderDrawColor(gWindow.getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(gWindow.getRenderer(), &m_collider);
}

void Projectile::debug()
{
	std::stringstream pos;
	pos.str(std::to_string(m_collider.x) + ',' + std::to_string(m_collider.y));

	Texture projectilePos{};
	projectilePos.loadFromRenderedText(pos.str().c_str(), gFuturaFont, SDL_Color(0x00, 0xFF, 0x00, 0xFF));
	projectilePos.scale(45, 20);


	switch (m_type)
	{
		case LEFT_PROJECTILE:
			if(m_vel.y < 0)
				projectilePos.render(m_collider.x - projectilePos.getWidth() - 1, m_collider.y - projectilePos.getHeight());

			else if(m_vel.y > 0)
				projectilePos.render(m_collider.x + m_collider.w, m_collider.y - projectilePos.getHeight());
			break;

		case RIGHT_PROJECTILE:
			if (m_vel.y < 0)
				projectilePos.render(m_collider.x + m_collider.w, m_collider.y - projectilePos.getHeight());

			else if (m_vel.y > 0)
				projectilePos.render(m_collider.x - projectilePos.getWidth() - 1, m_collider.y - projectilePos.getHeight());
			break;
	}

	drawCollision();
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

ProjectileType Projectile::getType()
{
	return m_type;
}

SDL_Rect& Projectile::getCollider()
{
	return m_collider;
}

void Projectile::setPos(Pair<int> pos)
{
	m_pos.x = pos.x;
	m_pos.y = pos.y;
}

void Projectile::setVel(Vector2<float> vel)
{
	m_vel.x = vel.x;
	m_vel.y = vel.y;
}

void Projectile::setTexture(Texture& texture)
{
	m_texture = texture;
}

void Projectile::setType(ProjectileType type)
{
	m_type = type;
}