#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../../Common/Pair.h"

class Movement
{
private:
	Vector2<float> m_vel;

public:
	Movement();

	void move(Vector2<float>& pos, double dt);

	void calculateVelocity(Vector2<float> direction, int speed);

	Vector2<float> getVel();
};

#endif // !MOVEMENT_H