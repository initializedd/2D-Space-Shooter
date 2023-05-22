#ifndef COLLIDER_H
#define COLLIDER_H

#include <SDL_rect.h>

class Collider
{
private:
	SDL_Rect m_rect;

public:
	Collider(SDL_Rect& rect);

	bool Intersects(const Collider& collider);
};

#endif // !COLLIDER_H