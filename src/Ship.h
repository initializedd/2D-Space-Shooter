#ifndef SHIP_H
#define SHIP_H

#include "Texture.h"
#include "Weapon.h"
#include "Particle.h"
#include "Pair.h"

// 33 Total Player ships -- SCK
// 21 Total Player Ships -- SCK2

class Ship
{
private:
	Texture					m_texture;
	SDL_Rect				m_clips[33];
	//Weapon					m_weapon;
	Particle				m_exhaustParticle;
	Pair<int>				m_leftProjectilePos;
	Pair<int>				m_rightProjectilePos;

public:
	Ship();
	~Ship();

	void setClipsFromSprite(int width, int height, int padding, int elements);

	Texture& getTexture();
	SDL_Rect* getClips();
};

#endif // !SHIP_H