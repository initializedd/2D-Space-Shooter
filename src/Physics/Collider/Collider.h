#ifndef COLLIDER_H
#define COLLIDER_H

#include "../../Common/Pair.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

class Collider
{
private:
	SDL_FRect m_rect;
	Vector2<int> m_offset;

public:
	Collider();
	Collider(const SDL_FRect& rect);

	bool intersects(const Collider& collider);

	void handleCollision(Vector2<float>& pos, const Vector2<float>& otherPos, const Collider& collider);
	bool handleScreenCollision(Vector2<float>& pos, double rotation);

	void drawCollider();

	const SDL_FRect& getRect() const;

	void createColliders(Vector2<float>& pos, double rotation);
};

#endif // !COLLIDER_H
