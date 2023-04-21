#include "Particle.h"

Particle::Particle()
	: m_texture{}
	, m_clips{}
{
}

Particle::~Particle()
{
}

Texture& Particle::getTexture()
{
	return m_texture;
}

SDL_Rect* Particle::getClips()
{
	return m_clips;
}

/*
 * Calculates the coordinates of each texture in a sprite and then assigns
 * each coordinate to its corresponding element in an SDL_Rect array.
 *
 * @note This function assumes the sprite is aligning each texture using a
 * binary tree algorithm for size efficiency.
 *
 * @param[in] width of textures within sprite
 * @param[in] height of textures within sprite
 * @param[in] padding of textures within sprite
 */
void Particle::setClipsFromSprite(int width, int height, int padding, int elements)
{
	for (int i = 0; i < elements; ++i)
	{
		m_clips[i].x = i * (width + padding) + (padding / 2);
		m_clips[i].y = padding / 2;
		m_clips[i].w = width;
		m_clips[i].h = height;
	}
}