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

std::vector<SDL_Rect>& Enemy::getColliders()
{
	return m_colliders;
}


Texture& Enemy::getTexture()
{
	return m_texture;
}

int Enemy::getPosX() const
{
	return m_pos.x;
}

int Enemy::getPosY() const
{
	return m_pos.y;
}

void Enemy::setCollider()
{
	m_colliders[0].x = gEnemyHeadCollision.x + m_pos.x;
	m_colliders[0].y = gEnemyHeadCollision.y + m_pos.y;

	m_colliders[1].x = gEnemyBodyCollision.x + m_pos.x;
	m_colliders[1].y = gEnemyBodyCollision.y + m_pos.y;
}