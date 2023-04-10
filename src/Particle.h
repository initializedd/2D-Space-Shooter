#ifndef PARTICLE_H
#define PARTICLE_H

#include "Texture.h"
#include <SDL_rect.h>

class Particle
{
private:
	Texture			m_texture;
	SDL_Rect		m_clips[6];

public:
	Particle();
	~Particle();

	Texture& getTexture();
	SDL_Rect* getClips();

	void setClipsFromSprite(int width, int height, int padding);
};

#endif // !PARTICLE_H