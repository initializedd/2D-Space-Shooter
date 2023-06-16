#include "WraithEnemy.h"
#include "Common.h"

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

void WraithEnemy::checkScreenBoundaryX()
{
	for (int i = 0; i < m_ship.getParts().size(); ++i)
	{
		const SDL_Rect& collider = m_ship.getParts()[i].getCollider().getRect();

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
		const SDL_Rect& collider = m_ship.getParts()[i].getCollider().getRect();

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