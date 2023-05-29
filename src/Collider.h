#ifndef COLLIDER_H
#define COLLIDER_H

#include "Pair.h"
#include <SDL_rect.h>

class Collider
{
private:
	SDL_Rect m_rect;
	Vector2<int> m_offset;

public:
	Collider();
	Collider(SDL_Rect& rect);

	bool intersects(const Collider& collider);

	void handleCollision(Vector2<float>& pos, const Vector2<float>& otherPos, Collider& collider, double rotation);
	bool handleScreenCollision(Vector2<float>& pos, double rotation);

	SDL_Rect& getRect();

	void setColliders(Vector2<float>& pos, double rotation);
};

#endif // !COLLIDER_H