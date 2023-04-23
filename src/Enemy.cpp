#include "Enemy.h"
#include "Globals.h"

Enemy::Enemy(int x, int y)
	: m_flameFrames{}
	, m_explosionFrames{}
{
	m_pos.x = x;
	m_pos.y = y;

	m_vel.x = ENEMY_VEL;

	m_colliders.push_back(gEnemyHeadCollision);
	m_colliders.push_back(gEnemyBodyCollision);

	m_health = 100;
}

Enemy::~Enemy()
{
}

void Enemy::move()
{
	// Update X position based on its X velocity
	m_pos.x += m_vel.x;
	setColliders();

	// Check if outside of left screen boundary
	if (m_pos.x <= 0)
	{
		m_pos.x = 0;
		setColliders();

		m_vel.x = ENEMY_VEL;
	}
	// Check if outside of right screen boundary
	else if (m_pos.x + gEnemyTexture.getWidth() >= SCREEN_WIDTH)
	{
		m_pos.x = SCREEN_WIDTH - gEnemyTexture.getWidth();
		setColliders();

		m_vel.x = -ENEMY_VEL;
	}
	// Check if collision on X axis
	else if (checkCollisionPosX(gWave.getEnemies()))
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
	else if (m_pos.y + gEnemyTexture.getHeight() + m_particle.getTexture().getHeight() >= SCREEN_HEIGHT)
	{
		m_pos.y = SCREEN_HEIGHT - gEnemyTexture.getHeight() - m_particle.getTexture().getHeight();
		setColliders();
	}
	// Check if collision on Y axis
	else if (checkCollisionPosY(gWave.getEnemies()))
	{
		setColliders();
	}
}

bool Enemy::checkCollisionPosX(std::vector<Enemy>& enemies)
{
	for (int i = 0; i < enemies.size(); ++i)
	{
		for (int j = 0; j < this->m_colliders.size(); ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				if (&enemies.at(i) != this)
				{
					if (SDL_HasIntersection(&m_colliders[j], &enemies.at(i).getColliders().at(k)))
					{
						/*if (m_pos.x <= enemies.at(i).getPosX())
						{
							m_pos.x = (enemies.at(i).getPosX() - (enemies.at(i).getPosX() - enemies.at(i).getColliders().at(k).x)) - ((m_colliders[j].x - m_pos.x) + m_colliders[j].w);
							m_vel.x = -ENEMY_VEL;
						}

						if (m_pos.x > enemies.at(i).getPosX())
						{
							m_pos.x = (enemies.at(i).getColliders().at(k).x + enemies.at(i).getColliders().at(k).w) - (m_colliders[j].x - m_pos.x);
							m_vel.x = ENEMY_VEL;
						}*/
						
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool Enemy::checkCollisionPosY(std::vector<Enemy>& enemies)
{
	for (int i = 0; i < enemies.size(); ++i)
	{
		for (int j = 0; j < this->m_colliders.size(); ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				if (&enemies.at(i) != this)
				{
					if (SDL_HasIntersection(&m_colliders[j], &enemies.at(i).getColliders().at(k)))
					{
						/*if (m_pos.y <= enemies.at(i).getPosY())
						{
							m_pos.y = (enemies.at(i).getPosY() - (enemies.at(i).getPosY() - enemies.at(i).getColliders().at(k).y)) - ((m_colliders[j].y - m_pos.y) + m_colliders[j].h);
							m_vel.y = -ENEMY_VEL;
						}

						if (m_pos.y > enemies.at(i).getPosY())
						{
							m_pos.y = (enemies.at(i).getColliders().at(k).y + enemies.at(i).getColliders().at(k).h) - (m_colliders[j].y - m_pos.y);
							m_vel.y = ENEMY_VEL;
						}*/

						return true;
					}
				}
			}
		}
	}

	return false;
}

void Enemy::exhaustAnimation()
{
	SDL_Rect* currentClip = &gExhaustParticle.getClips()[m_flameFrames / 3];

	// Left Exhaust
	gExhaustParticle.getTexture().render(this->getPosX() + 35, this->getPosY() + 49, currentClip, gExhaustParticle.getTexture().getWidth(), gExhaustParticle.getTexture().getHeight(), 0, nullptr, SDL_FLIP_HORIZONTAL);

	// Right Exhaust
	gExhaustParticle.getTexture().render(this->getPosX() + 115, this->getPosY() + 49, currentClip, gExhaustParticle.getTexture().getWidth(), gExhaustParticle.getTexture().getHeight());

	++m_flameFrames;
	if (m_flameFrames / 3 >= 6)
	{
		m_flameFrames = 0;
	}
}

int Enemy::deathAnimation()
{
	SDL_Rect* currentClip = &gExplosionParticle.getClips()[m_explosionFrames / 2];

	int explosionPosX = (this->getPosX() + gEnemyTexture.getWidth() / 2) - gExplosionParticle.getTexture().getWidth() / 2;
	int explosionPosY = (this->getPosY() + gEnemyTexture.getHeight() / 2) - gExplosionParticle.getTexture().getHeight() / 2;

	gExplosionParticle.getTexture().render(explosionPosX, explosionPosY, currentClip, gExplosionParticle.getTexture().getWidth(), gExplosionParticle.getTexture().getHeight());

	++m_explosionFrames;
	return m_explosionFrames;
}

void Enemy::setColliders()
{
	m_colliders[0].x = gEnemyHeadCollision.x + m_pos.x;
	m_colliders[0].y = gEnemyHeadCollision.y + m_pos.y;

	m_colliders[1].x = gEnemyBodyCollision.x + m_pos.x;
	m_colliders[1].y = gEnemyBodyCollision.y + m_pos.y;
}