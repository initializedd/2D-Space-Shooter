#include "Projectile.h"
#include "Globals.h"
#include "Constants.h"
#include <cstdio>

Projectile::Projectile()
	: m_pos{}
	, m_vel{}
	, m_texture{}
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
		// Check for collision
		if (SDL_HasIntersection(&this->getCollider(), &enemies.at(i).getColliders().at(0)) || SDL_HasIntersection(&this->getCollider(), &enemies.at(i).getColliders().at(1)))
		{
			if (!enemies.at(i).isDead())
			{
				enemies.at(i).reduceHealth(m_damage);

				if (enemies.at(i).isDead())
				{
					gExplosionSound.playChunk(-1, 0, 10);
				}
			}

			return true;
		}
	}

	return false;
}

bool Projectile::checkCollision(Player& player)
{
	for (int i = 0; i < player.getColliders().size(); ++i)
	{
		// Check for collision
		if (SDL_HasIntersection(&this->getCollider(), &player.getColliders().at(i)))
		{
			if (!player.isDead())
			{
				player.reduceHealth(m_damage);

				if (player.isDead())
				{
					gExplosionSound.playChunk(-1, 0, 10);
				}
			}

			return true;
		}
	}

	return false;
}

void Projectile::drawCollision()
{
	SDL_SetRenderDrawColor(gWindow.getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(gWindow.getRenderer(), &this->getCollider());
}

void Projectile::debug(ProjectileType type)
{
	std::stringstream pos;
	pos.str(std::to_string(m_collider.x) + ',' + std::to_string(m_collider.y));

	Texture cannonPos{};
	cannonPos.loadFromRenderedText(pos.str().c_str(), gFuturaFont, SDL_Color(0x00, 0xFF, 0x00, 0xFF));
	cannonPos.resize(cannonPos.getWidth() / 2, cannonPos.getHeight() / 2);
	

	switch (type)
	{
	case LEFT_PROJECTILE:
		cannonPos.render(m_collider.x - cannonPos.getWidth() - 1, m_collider.y - cannonPos.getHeight());
		break;

	case RIGHT_PROJECTILE:
		cannonPos.render(m_collider.x + m_collider.w, m_collider.y - cannonPos.getHeight());
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