#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <sstream>
#include <SDL_events.h>

class Player : public Entity
{
private:
	int							m_flameFrames;
	Texture						m_healthTexture;
	std::stringstream			m_healthText;

public:
	Player(int x, int y);
	~Player();

	void handleEvent(SDL_Event& event);
	void update(int i, double dt);
	void render();

	bool displayHealth();

	Texture& getHealhTexture();
};

#endif // !PLAYER_H