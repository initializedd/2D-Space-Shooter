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

void Projectile::move(int vel)
{
	m_pos.y -= vel;
}

bool Projectile::checkCollision(std::vector<Enemy>& enemies)
{
	for (int i = 0; i < enemies.size(); ++i)
	{
		for ( int j = 0; j < enemies[i].getColliders().size(); ++j)
		{
			// Check for collision
			if (SDL_HasIntersection(&this->getCollider(), &enemies[i].getColliders()[j]))
			{
				if (!enemies[i].isDead())
				{
					enemies[i].reduceHealth(m_damage);

					if (enemies[i].isDead())
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

bool Projectile::checkCollision(Player& player)
{
	for (int i = 0; i < player.getColliders().size(); ++i)
	{
		// Check for collision
		if (SDL_HasIntersection(&this->getCollider(), &player.getColliders()[i]))
		{
			if (!player.isDead())
			{
				player.reduceHealth(m_damage);

				if (player.isDead())
				{
					gExplosionSound.playChunk(-1, 0, 10);
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

void Projectile::drawCollision()
{
	SDL_SetRenderDrawColor(gWindow.getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(gWindow.getRenderer(), &this->getCollider());
}

void Projectile::debug()
{
	std::stringstream pos;
	pos.str(std::to_string(m_collider.x) + ',' + std::to_string(m_collider.y));

	Texture projectilePos{};
	projectilePos.loadFromRenderedText(pos.str().c_str(), gFuturaFont, SDL_Color(0x00, 0xFF, 0x00, 0xFF));
	projectilePos.scale(projectilePos.getWidth() / 2, projectilePos.getHeight() / 2);


	switch (m_type)
	{
		case LEFT_PROJECTILE:
			projectilePos.render(m_collider.x - projectilePos.getWidth() - 1, m_collider.y - projectilePos.getHeight());
			break;

		case RIGHT_PROJECTILE:
			projectilePos.render(m_collider.x + m_collider.w, m_collider.y - projectilePos.getHeight());
			break;
	}

	this->drawCollision();
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

void Projectile::setVel(Pair<int> vel)
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

void Projectile::setCollider(SDL_Rect box)
{
	m_collider = box;
}