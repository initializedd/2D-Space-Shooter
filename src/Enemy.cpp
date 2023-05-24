#include "Enemy.h"
#include "Globals.h"

Enemy::Enemy(int x, int y)
	: m_flameFrames{}
{
	m_type = ENEMY;
	m_textureRotation = 180.f;

	m_direction = Vector2<float>(0, 1);

	m_weapon = m_type;
	m_id = ENTITY_ID;

	m_pos.x = x;
	m_pos.y = y;

	m_vel.x = ENEMY_SPEED;

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
		//shoot(500);
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
		// Exhaust Textures
		for(int i = 0; i < m_ship.getParts().size(); ++i)
		{
			ShipPart& part = m_ship.getParts()[i];
			SDL_Rect& collider = part.getCollider().getRect();

			if (part.getPartType() == LEFT_EXHAUST || part.getPartType() == RIGHT_EXHAUST)
			{
				gExhaustParticle.getTexture().render(collider.x, collider.y, m_currentExhaustClip, collider.w, collider.h);
			}
			else if (part.getPartType() == EXHAUST)
			{
				gExhaustParticle.getTexture().render(collider.x, collider.y, m_currentExhaustClip, collider.w, collider.h);
				gExhaustParticle.getTexture().render(collider.x, collider.y, m_currentExhaustClip, collider.w, collider.h, 0, nullptr, SDL_FLIP_HORIZONTAL);
			}
		}

		// Ship Texture
		m_ship.getTexture().render(m_pos.x, m_pos.y, &m_ship.getTexture().getClips()[m_ship.getTexture().getIndex()], m_ship.getTexture().getClips()[m_ship.getTexture().getIndex()].w, m_ship.getTexture().getClips()[m_ship.getTexture().getIndex()].h, 180);
	}

	// Projejctiles
	m_weapon.renderProjectiles();

	if (isDead())
	{
		renderDeathAnimation();
	}
}