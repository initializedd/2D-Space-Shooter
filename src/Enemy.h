#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity
{
private:
	int				m_flameFrames;

public:
	Enemy(int x, int y);

	void update(int i, double dt);
	void render();
};

#endif // !ENEMY_H