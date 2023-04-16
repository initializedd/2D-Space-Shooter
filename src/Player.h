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

	bool checkCollisionPosX(std::vector<SDL_Rect>& box);
	bool checkCollisionPosY(std::vector<SDL_Rect>& box);

	std::vector<SDL_Rect>& getColliders();
	Texture& getTexture();
	Particle& getParticle();
	Weapon& getWeapon();
	int getPosX() const;
	int getPosY() const;

	void setColliders();
};

#endif // !PLAYER_H