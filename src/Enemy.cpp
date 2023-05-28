#include "Enemy.h"
#include "Globals.h"

Enemy::Enemy(int x, int y)
	: m_flameFrames{}
{
	m_health = 200;

	m_width = 64;
	m_height = 80;

	m_type = ENEMY;
	m_textureRotation = 180.f;

	m_direction = Vector2<float>(0, 1);

	m_weapon = { m_type, Vector2<float>(0, 1) };

	m_pos.x = x;
	m_pos.y = y;

	m_vel.x = ENEMY_SPEED;
}

void Enemy::update(int i, double dt)
{
	m_weapon.updateProjectiles(dt);

	if (!isDead())
	{
		move(dt);
		exhaustAnimation();
		shoot(1000);
	}
	else
	{
		if (deathAnimation() && m_weapon.getProjectiles().empty())
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
		for (int i = 0; i < m_ship.getParts().size(); ++i)
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
		m_ship.getTexture().render(m_pos.x, m_pos.y, &m_ship.getTexture().getClips()[m_ship.getTexture().getIndex()], m_width, m_height, 180);
	}

	// Projejctiles
	m_weapon.renderProjectiles();

	if (isDead())
	{
		renderDeathAnimation();
	}
}

void Enemy::checkScreenBoundaryX()
{
	for (int i = 0; i < m_ship.getParts().size(); ++i)
	{
		SDL_Rect& collider = m_ship.getParts()[i].getCollider().getRect();

		// Check if outside of left screen boundary
		if (collider.x < 0.f)
		{
			m_pos.x += std::abs(collider.x);

			setColliders();

			calculateVelocity(Vector2<float>(1.f, 0.f), ENEMY_SPEED);
		}

		// Check if outside of right screen boundary
		if (collider.x + collider.w > SCREEN_WIDTH)
		{
			float difference = std::abs(collider.x - m_pos.x);
			m_pos.x = SCREEN_WIDTH - collider.w - difference;

			setColliders();

			calculateVelocity(Vector2<float>(-1.f, 0.f), ENEMY_SPEED);
		}
	}
}