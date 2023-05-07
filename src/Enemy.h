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

	void shoot(int delay);
	void update(int i);

	void exhaustAnimation();

	void setColliders();
};

#endif // !ENEMY_H