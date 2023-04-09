#ifndef PARTICLE_H
#define PARTICLE_H

#include "Texture.h"
#include <SDL_rect.h>

class Particle
{
private:
	Texture		m_sprite;
	SDL_Rect	m_clips[6];

public:
	Particle();
	~Particle();
};

#endif // !PARTICLE_H