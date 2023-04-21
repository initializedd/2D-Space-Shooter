#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <SDL_events.h>

class Player : public virtual Entity
{
private:
	int m_flameFrames;

public:
	Player();
	~Player();

	void handleEvent(SDL_Event& event);
	void move();

	void exhaustAnimation();

	bool checkCollisionPosX(std::vector<Enemy>& enemies);
	bool checkCollisionPosY(std::vector<Enemy>& enemies);

	void setColliders();
};

#endif // !PLAYER_H