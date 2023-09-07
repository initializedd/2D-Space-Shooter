#include "Enemy.h"
#include "../../Common/Common.h"
#include "../../Game/Game.h"

Enemy::Enemy(int x, int y)
	: m_flameFrames{}
{
	m_health = 200;

	m_width = 64;
	m_height = 80;

	m_type = ENEMY;
	m_textureRotation = 180.f;

	m_direction = Vector2<float>(1, 0);

	m_weapon = { m_type, Vector2<float>(0, 1) };

	m_pos.x = x;
	m_pos.y = y;

	m_speed = ENEMY_SPEED;
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
			gEnts.erase(gEnts.begin() + i);
		}
	}
}

void Enemy::render()
{
	if (!isDead())
	{
		std::shared_ptr<Sprite> fire = resourceManager.getTextureSystem().findSprite("sprite_fire");

		// Exhaust Textures
		for (int i = 0; i < m_ship.getParts().size(); ++i)
		{
			ShipPart& part = m_ship.getParts()[i];
			const SDL_Rect& collider = part.getCollider().getRect();

			if (part.getPartType() == LEFT_EXHAUST || part.getPartType() == RIGHT_EXHAUST)
			{
				fire->render(collider.x, collider.y, collider.w, collider.h, m_currentExhaustClip);
			}
			else if (part.getPartType() == EXHAUST)
			{
				fire->render(collider.x, collider.y, collider.w, collider.h, m_currentExhaustClip);
				fire->render(collider.x, collider.y, collider.w, collider.h, m_currentExhaustClip, 0, nullptr, SDL_FLIP_HORIZONTAL);
			}
		}

		std::shared_ptr<Sprite> ship = resourceManager.getTextureSystem().findSprite("sprite_ships");

		// Ship Texture
		ship->render(m_pos.x, m_pos.y, 64 * sf.x, 80 * sf.y, &ship->getClips()[m_ship.getIndex()], 180);
	}

	// Projejctiles
	m_weapon.renderProjectiles();

	if (isDead())
	{
		renderDeathAnimation();
	}
}