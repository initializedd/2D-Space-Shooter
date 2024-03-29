#include "Movement.h"
#include "../../Common/Common.h"

Movement::Movement()
	: m_vel{}
{
}

void Movement::move(Vector2<float>& pos, double dt)
{
	// Update X position based on its X velocity
	pos.x += m_vel.x * dt;

	// Update Y position based on its Y velocity
	pos.y += m_vel.y * dt;
}

void Movement::calculateVelocity(Vector2<float> direction, int speed)
{
	m_vel.x = direction.x * speed * sf.x;
	m_vel.y = direction.y * speed * sf.y;
}

Vector2<float> Movement::getVel()
{
	return m_vel;
}