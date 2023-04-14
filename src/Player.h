#ifndef PLAYER_H
#define PLAYER_H

#include "Texture.h"
#include "Particle.h"
#include "Weapon.h"
#include "Pair.h"
#include <SDL_events.h>

class Player
{
private:
	Texture					m_texture;
	int						m_width;
	int						m_height;

	Pair<int>				m_pos;
	Pair<int>				m_vel;

	SDL_Rect				m_collider;

	int						m_health;

	Particle				m_particle;

	Weapon					m_weapon;

public:
	Player();
	~Player();

	void handleEvent(SDL_Event& event);

	void move();
	void shoot();
	void animateExhaust(int flameFrames);

	bool checkCollision(SDL_Rect& box);

	SDL_Rect& getCollider();
	Texture& getTexture();
	Particle& getParticle();
	Weapon& getWeapon();
	int getPosX() const;
	int getPosY() const;

	void setCollider();
};

#endif // !PLAYER_H