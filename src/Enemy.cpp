#include "Enemy.h"
#include "Globals.h"

Enemy::Enemy(int x, int y)
	: m_texture{}
	, m_width{}
	, m_height{}
	, m_vel{}
	, m_health{}
	, m_particle{}
	, m_weapon{}
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

void Enemy::move()
{

}

void Enemy::shoot()
{
	m_weapon.shoot();
}

void Enemy::animateExhaust(int flameFrames)
{
	SDL_Rect* currentClip = &gExhaustParticle.getClips()[flameFrames / 6];

	// Left Exhaust
	gExhaustParticle.getTexture().render(this->getPosX() + 37, this->getPosY() + 57, currentClip, gExhaustParticle.getTexture().getWidth(), gExhaustParticle.getTexture().getHeight(), 0, nullptr, SDL_FLIP_HORIZONTAL);

	// Right Exhaust
	gExhaustParticle.getTexture().render(this->getPosX() + 115, this->getPosY() + 57, currentClip, gExhaustParticle.getTexture().getWidth(), gExhaustParticle.getTexture().getHeight());
}

bool Enemy::checkCollision(SDL_Rect& box)
{
	this->setCollider();

	for (int i = 0; i < this->getColliders().size(); ++i)
	{
		if (SDL_HasIntersection(&this->getColliders().at(i), &box))
			return true;
	}

	return false;
}

bool Enemy::isDead()
{
	return m_health <= 0;
}

void Enemy::reduceHealth(int damage)
{
	m_health -= damage;
}

std::vector<SDL_Rect>& Enemy::getColliders()
{
	return m_colliders;
}

Texture& Enemy::getTexture()
{
	return m_texture;
}

Particle& Enemy::getParticle()
{
	return m_particle;
}

int Enemy::getPosX() const
{
	return m_pos.x;
}

int Enemy::getPosY() const
{
	return m_pos.y;
}

int Enemy::getHealth() const
{
	return m_health;
}

int Enemy::getWidth() const
{
	return m_width;
}

int Enemy::getHeight() const
{
	return m_height;
}

void Enemy::setCollider()
{
	m_colliders[0].x = gEnemyHeadCollision.x + m_pos.x;
	m_colliders[0].y = gEnemyHeadCollision.y + m_pos.y;

	m_colliders[1].x = gEnemyBodyCollision.x + m_pos.x;
	m_colliders[1].y = gEnemyBodyCollision.y + m_pos.y;
}