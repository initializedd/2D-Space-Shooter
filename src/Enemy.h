#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity
{
private:
	int				m_flameFrames;

public:
	Enemy(int x, int y);
	~Enemy();

	void update(int i, double dt);
	void render();

	void exhaustAnimation(double dt);

	void setColliders();
	void setCannonColliders();
};

#endif // !ENEMY_H