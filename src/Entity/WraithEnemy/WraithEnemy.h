#ifndef WRAITH_ENEMY_H
#define WRAITH_ENEMY_H

#include "../Enemy/Enemy.h"

class WraithEnemy : public Enemy
{
public:
	WraithEnemy(int x, int y);

	void move(double dt);
	void shoot(int delay);

	void checkScreenBoundaryX();
	void checkScreenBoundaryY();
};

#endif // !WRAITH_ENEMY_H