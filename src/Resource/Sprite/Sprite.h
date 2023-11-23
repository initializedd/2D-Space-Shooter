#ifndef SPRITE_H
#define SPRITE_H

#include "../Texture/Texture.h"

class Sprite : public Texture
{
private:
	SDL_FRect		m_clips[48];
	int				m_index;

public:
	Sprite();
	~Sprite();

	SDL_FRect* getClips();
	int getIndex();

	void setClipsFromSprite(int width, int height, int padding, int elements);
	void setIndex(int index);
};

#endif // !SPRITE_H
