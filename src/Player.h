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

	std::vector<SDL_Rect>	m_colliders;

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

	bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b);
	void shiftColliders();

	std::vector<SDL_Rect>& getColliders();
	Texture& getTexture();
	Particle& getParticle();
	Weapon& getWeapon();
	int getPosX() const;
	int getPosY() const;

	bool setTexture(const char* path, const bool flag, const Uint8 red = 0xFF, const Uint8 green = 0xFF, const Uint8 blue = 0xFF);
};

#endif // !PLAYER_H