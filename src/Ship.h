#ifndef SHIP_H
#define SHIP_H

#include "ShipPart.h"
#include "Texture.h"
#include "Weapon.h"
#include "Particle.h"
#include "Pair.h"

// 33 Total Player ships -- SCK
// 21 Total Player Ships -- SCK2

class Ship
{
private:
	std::vector<ShipPart>	m_parts;
	int						m_index;
	Texture					m_texture;
	SDL_Rect				m_clips[33];
	//Weapon					m_weapon;
	Particle				m_exhaustParticle;

public:
	Ship();
	~Ship();

	void createShip(int index);

	void setClipsFromSprite(int width, int height, int padding, int elements);

	Texture& getTexture();
	SDL_Rect* getClips();
};

#endif // !SHIP_H