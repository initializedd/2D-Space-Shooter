#ifndef COLLIDER_H
#define COLLIDER_H

#include "Pair.h"
#include <SDL_rect.h>
#include <SDL_render.h>

class Collider
{
private:
	SDL_Rect m_rect;
	Vector2<int> m_offset;

public:
	Collider();
	Collider(SDL_Rect& rect);

	bool intersects(const Collider& collider);

	void handleCollision(Vector2<float>& pos, const Vector2<float>& otherPos, const Collider& collider);
	bool handleScreenCollision(Vector2<float>& pos, double rotation);

	void drawCollider();

	const SDL_Rect& getRect() const;

	void setColliders(Vector2<float>& pos, double rotation);
};

#endif // !COLLIDER_H