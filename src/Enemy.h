#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity
{
private:
	int				m_flameFrames;
	bool			m_canShoot;

public:
	Enemy(int x, int y);
	~Enemy();

	void move();
	void shoot(int delay);

	bool checkCollisionPosX(std::vector<Enemy>& enemies);
	bool checkCollisionPosY(std::vector<Enemy>& enemies);

	void exhaustAnimation();

	void setColliders();
};

#endif // !ENEMY_H