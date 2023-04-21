#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public virtual Entity
{
private:
	int				m_flameFrames;
	int				m_explosionFrames;

public:
	Enemy(int x, int y);
	~Enemy();

	void exhaustAnimation();
	int deathAnimation();

	void setCollider();
};

#endif // !ENEMY_H