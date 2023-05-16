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

	gExhaustParticle.getTexture().scale(400 * 0.035, 400 * 0.035);

	++ENTITY_ID;
}

Enemy::~Enemy()
{
	--ENTITY_ID;
}

void Enemy::update(int i, double dt)
{
	getWeapon().updateProjectiles(dt);

	if (!isDead())
	{
		move(dt);
		exhaustAnimation(dt);
		shoot(500);
	}
	else
	{
		if (deathAnimation(dt) && m_weapon.getProjectiles().empty())
		{
			delete this;
			gEnts.erase(gEnts.begin() + i);
		}
	}
}

void Enemy::render()
{
	if (!isDead())
	{
		// Ship Texture
		m_texture.render(m_pos.x, m_pos.y, nullptr, 0, 0, 180);

		// Left Ship Exhaust
		gExhaustParticle.getTexture().render(m_pos.x + 41, m_pos.y + 55, m_currentExhaustClip, gExhaustParticle.getTexture().getWidth(), gExhaustParticle.getTexture().getHeight(), 0, nullptr, SDL_FLIP_HORIZONTAL);

		// Right Ship Exhaust
		gExhaustParticle.getTexture().render(m_pos.x + 115, m_pos.y + 55, m_currentExhaustClip, gExhaustParticle.getTexture().getWidth(), gExhaustParticle.getTexture().getHeight());
	}

	// Projejctiles
	m_weapon.renderProjectiles();

	if (isDead())
	{
		renderDeathAnimation();
	}
}

void Enemy::exhaustAnimation(double dt)
{
	m_currentExhaustClip = &gExhaustParticle.getClips()[m_flameFrames / 3];

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
}

void Enemy::setCannonColliders()
{
	// Enemy left cannon pos
	m_leftCannonPos.x = 42 + m_pos.x;
	m_leftCannonPos.y = 89 + m_pos.y;

	// Enemy right cannon pos
	m_rightCannonPos.x = 70 + m_pos.x;
	m_rightCannonPos.y = 90 + m_pos.y;
}