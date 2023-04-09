#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>

class Texture
{
private:
	SDL_Texture*	m_texture;
	int				m_width;
	int				m_height;
	SDL_Surface*	m_surfacePixels;

public:
	Texture();
	~Texture();

	bool loadPixelsFromFile(const char* path);
	bool loadFromPixels(const bool flag, const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha);
	bool loadFromFile(const char* path, const bool flag, const Uint8 red = 0xFF, const Uint8 green = 0xFF, const Uint8 blue = 0xFF, const Uint8 alpha = 0xFF);

	void render(int x, int y, SDL_Rect* clip = nullptr, int scaleW = 0, int scaleH = 0, double angle = 0.0, SDL_Point* centre = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void resize(int width, int height);

	int getWidth();
	int getHeight();

	void free();
};

#endif // !TEXTURE_H