#include "Collider.h"

Collider::Collider(SDL_Rect& rect)
	: m_rect{rect}
{
}

bool Collider::Intersects(const Collider& collider)
{
	return SDL_HasIntersection(&m_rect, &collider.m_rect);
}