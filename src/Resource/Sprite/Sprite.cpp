#include "Sprite.h"

Sprite::Sprite()
	: m_clips{}
	, m_index{}
{
}

Sprite::~Sprite()
{
}

SDL_FRect* Sprite::getClips()
{
	return m_clips;
}

int Sprite::getIndex()
{
	return m_index;
}

/*
 * Calculates the coordinates of each texture in a sprite and then assigns
 * each coordinate to its corresponding element in an SDL_FRect array.
 *
 * @note This function assumes the sprite is aligning each texture by left align.
 *
 * @param[in] width of textures within sprite
 * @param[in] height of textures within sprite
 * @param[in] padding of textures within sprite
 */
void Sprite::setClipsFromSprite(int width, int height, int padding, int elements)
{
	for (int i = 0; i < elements; ++i)
	{
		m_clips[i].x = i * (width + padding) + (padding / 2);
		m_clips[i].y = padding / 2;
		m_clips[i].w = width;
		m_clips[i].h = height;
	}
}

void Sprite::setIndex(int index)
{
	m_index = index;
}
