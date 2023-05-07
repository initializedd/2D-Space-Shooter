#include "Enemy.h"
#include "Globals.h"

Enemy::Enemy(int x, int y)
	: m_flameFrames{}
{
	m_type = ENEMY;
	m_weapon = m_type;
	m_id = ENTITY_ID;

	m_pos.x = x;
	m_pos.y = y;

	m_vel.x = ENEMY_VEL;

	m_colliders.push_back(gEnemyHeadCollision);
	m_colliders.push_back(gEnemyBodyCollision);

	m_health = 100;

	++ENTITY_ID;
}

Enemy::~Enemy()
{
	--ENTITY_ID;
}

void Enemy::shoot(int delay)
{
	if (m_canShoot)
		m_weapon.shoot(m_leftProjectilePos, m_rightProjectilePos, delay);
}

void Enemy::update(int i)
{
 	if (!isDead())
	{
		move();
		exhaustAnimation();
		getTexture().render(m_pos.x, m_pos.y, nullptr, 0, 0, 180);
		shoot(500);
		getWeapon().updateProjectiles();
	}
	else
	{
		if (deathAnimation() / 2 >= 12)
		{
			delete this;
			gEnts.erase(gEnts.begin() + i);
		}
	}
}

void Enemy::exhaustAnimation()
{
	gExhaustParticle.getTexture().scale(400 * 0.035, 400 * 0.035);
	SDL_Rect* currentClip = &gExhaustParticle.getClips()[m_flameFrames / 3];

	// Left Exhaust
	gExhaustParticle.getTexture().render(m_pos.x + 41, m_pos.y + 55, currentClip, gExhaustParticle.getTexture().getWidth(), gExhaustParticle.getTexture().getHeight(), 0, nullptr, SDL_FLIP_HORIZONTAL);

	// Right Exhaust
	gExhaustParticle.getTexture().render(m_pos.x + 115, m_pos.y + 55, currentClip, gExhaustParticle.getTexture().getWidth(), gExhaustParticle.getTexture().getHeight());

	++m_flameFrames;
	if (m_flameFrames / 3 >= 6)
	{
		m_flameFrames = 0;
	}
}

void Enemy::setColliders()
{
	m_colliders[0].x = gEnemyHeadCollision.x + m_pos.x;
	m_colliders[0].y = gEnemyHeadCollision.y + m_pos.y;

	m_colliders[1].x = gEnemyBodyCollision.x + m_pos.x;
	m_colliders[1].y = gEnemyBodyCollision.y + m_pos.y;

	// Enemy projectile pos
	m_leftProjectilePos.x = 42 + m_pos.x;
	m_leftProjectilePos.y = 89 + m_pos.y;

	m_rightProjectilePos.x = 70 + m_pos.x;
	m_rightProjectilePos.y = 90 + m_pos.y;
}