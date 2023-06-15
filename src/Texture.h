#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL_render.h>
#include <SDL_ttf.h>
#include <string>

class Texture
{
protected:
	SDL_Texture*				m_texture;
	int							m_width;
	int							m_height;
	SDL_Surface*				m_surfacePixels;

public:
	Texture();
	~Texture();

	bool loadPixelsFromFile(const std::string& path);
	bool loadFromPixels(const bool flag, const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha);
	bool loadFromFile(const std::string& path, const bool flag, const Uint8 red = 0xFF, const Uint8 green = 0xFF, const Uint8 blue = 0xFF, const Uint8 alpha = 0xFF);
	bool loadFromRenderedText(const std::string& text, TTF_Font* font, SDL_Color textColor);

	void render(int x, int y, int w, int h, SDL_Rect* srcrect = nullptr, double angle = 0.0, SDL_Point* centre = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void scale(int width, int height);
	void free();

	SDL_Texture* getTexture();
	int getWidth();
	int getHeight();

	void setTexture(Texture& texture);
};

#endif // !TEXTURE_H