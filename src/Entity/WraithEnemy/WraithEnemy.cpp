#include "WraithEnemy.h"
#include "../../Common/Common.h"
#include <cmath>

WraithEnemy::WraithEnemy(int x, int y)
	: Enemy{ x, y }
{

	if (x > SCREEN_WIDTH / 2)
		m_direction.x = -1;
	else
		m_direction.x = 1;

	if (y > SCREEN_HEIGHT / 2)
		m_direction.y = -1;
	else
		m_direction.y = 1;

	//calculateVelocity(m_direction, ENEMY_SPEED);
}

void WraithEnemy::move(double dt)
{
	m_movement.calculateVelocity(m_direction, m_speed);

	m_movement.move(m_pos, dt);
	createColliders();

	checkScreenBoundaryX();
	checkScreenBoundaryY();
	checkCollision(gEnts);
}

void WraithEnemy::shoot(int delay)
{
	if (!isDead())
	{
		if (!m_lastShot.isStarted())
		{
			m_lastShot.start();
		}
		else if (m_lastShot.getTicks() < delay)
		{
			return; // not enough time has passed
		}
		m_lastShot.start();

		Pair<int> leftProjectilePos{};
		Pair<int> rightProjectilePos{};

		for (int i = 0; i < m_ship.getParts().size(); ++i)
		{
			ShipPart& part = m_ship.getParts()[i];
			if (part.getPartType() == LEFT_WEAPON)
			{
				leftProjectilePos.x = (m_ship.getParts()[i].getCollider().getRect().x) - (gLeftProjectileHitBox.x - (std::round(m_ship.getParts()[i].getCollider().getRect().w / 2) - (gLeftProjectileHitBox.w / 2)));	// Centre the projectile
				leftProjectilePos.y = m_ship.getParts()[i].getCollider().getRect().y;
			}
			else if (part.getPartType() == RIGHT_WEAPON)
			{
				rightProjectilePos.x = (m_ship.getParts()[i].getCollider().getRect().x) - (gRightProjectileHitBox.x - (std::round(m_ship.getParts()[i].getCollider().getRect().w / 2) - (gRightProjectileHitBox.w / 2))); // Centre the projectile;
				rightProjectilePos.y = m_ship.getParts()[i].getCollider().getRect().y;
			}
		}

		m_weapon.shoot(leftProjectilePos, rightProjectilePos);
	}
}

void WraithEnemy::checkScreenBoundaryX()
{
	for (int i = 0; i < m_ship.getParts().size(); ++i)
	{
		const SDL_FRect& collider = m_ship.getParts()[i].getCollider().getRect();

		// Check if outside of left screen boundary
		if (collider.x < 0.f)
		{
			m_pos.x += std::abs(collider.x);

			createColliders();

			m_direction.x = 1;
		}

		// Check if outside of right screen boundary
		if (collider.x + collider.w > SCREEN_WIDTH)
		{
			float difference = std::abs(collider.x - m_pos.x);
			m_pos.x = SCREEN_WIDTH - collider.w - difference;

			createColliders();

			m_direction.x = -1;
		}
	}
}

void WraithEnemy::checkScreenBoundaryY()
{
	for (int i = 0; i < m_ship.getParts().size(); ++i)
	{
		const SDL_FRect& collider = m_ship.getParts()[i].getCollider().getRect();

		// Check if outside of top screen boundary
		if (collider.y < 0.f)
		{
			m_pos.y += std::abs(collider.y);

			createColliders();

			m_direction.y = 1;
		}

		// Check if outside of bottom screen boundary
		if (collider.y + collider.h > SCREEN_HEIGHT / 2)
		{
			float difference = std::abs(collider.y - m_pos.y);
			m_pos.y = SCREEN_HEIGHT / 2 - collider.h - difference;

			createColliders();

			m_direction.y = -1;
		}
	}
}
