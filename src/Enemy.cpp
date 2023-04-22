#include "Enemy.h"
#include "Globals.h"

Enemy::Enemy(int x, int y)
	: m_flameFrames{}
	, m_explosionFrames{}
{
	m_pos.x = x;
	m_pos.y = y;

	m_colliders.push_back(gEnemyHeadCollision);
	m_colliders.push_back(gEnemyBodyCollision);

	m_health = 100;
}

Enemy::~Enemy()
{
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

void Enemy::setCollider()
{
	m_colliders[0].x = gEnemyHeadCollision.x + m_pos.x;
	m_colliders[0].y = gEnemyHeadCollision.y + m_pos.y;

	m_colliders[1].x = gEnemyBodyCollision.x + m_pos.x;
	m_colliders[1].y = gEnemyBodyCollision.y + m_pos.y;
}