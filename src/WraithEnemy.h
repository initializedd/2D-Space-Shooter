#ifndef WRAITH_ENEMY_H
#define WRAITH_ENEMY_H

#include "Enemy.h"

class WraithEnemy : public Enemy
{
public:
	WraithEnemy(int x, int y);

	void move(double dt);

	void checkScreenBoundaryX();
	void checkScreenBoundaryY();
};

#endif // !WRAITH_ENEMY_H