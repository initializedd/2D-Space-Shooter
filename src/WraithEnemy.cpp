#include "WraithEnemy.h"
#include "Constants.h"
#include "Globals.h"

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

	calculateVelocity(m_direction, ENEMY_SPEED);
}

void WraithEnemy::move(double dt)
{
	// Update X position based on its X velocity
	m_pos.x += m_vel.x * dt;
	setColliders();

	// Check if outside screen boundary X
	checkScreenBoundaryX();

	// Check for collision on X axis
	if (checkCollisionPosX(gEnts))
	{
		setColliders();
	}

	// Update Y position based on its Y velocity
	m_pos.y += m_vel.y * dt;
	setColliders();

	// Check if outside screen boundary Y
	checkScreenBoundaryY();

	// Check for collision on Y axis
	if (checkCollisionPosY(gEnts))
	{
		setColliders();
	}
	
	calculateVelocity(m_direction, ENEMY_SPEED);
}

void WraithEnemy::checkScreenBoundaryX()
{
	for (int i = 0; i < m_ship.getParts().size(); ++i)
	{
		SDL_Rect& collider = m_ship.getParts()[i].getCollider().getRect();

		// Check if outside of left screen boundary
		if (collider.x < 0.f)
		{
			m_pos.x += std::abs(collider.x);

			setColliders();

			m_direction.x = 1;
		}

		// Check if outside of right screen boundary
		if (collider.x + collider.w > SCREEN_WIDTH)
		{
			float difference = std::abs(collider.x - m_pos.x);
			m_pos.x = SCREEN_WIDTH - collider.w - difference;

			setColliders();

			m_direction.x = -1;
		}
	}
}

void WraithEnemy::checkScreenBoundaryY()
{
	for (int i = 0; i < m_ship.getParts().size(); ++i)
	{
		SDL_Rect& collider = m_ship.getParts()[i].getCollider().getRect();

		// Check if outside of top screen boundary
		if (collider.y < 0.f)
		{
			m_pos.y += std::abs(collider.y);

			setColliders();

			m_direction.y = 1;
		}

		// Check if outside of bottom screen boundary
		if (collider.y + collider.h > SCREEN_HEIGHT / 2)
		{
			float difference = std::abs(collider.y - m_pos.y);
			m_pos.y = SCREEN_HEIGHT / 2 - collider.h - difference;

			setColliders();

			m_direction.y = -1;
		}
	}
}