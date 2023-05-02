#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL_render.h>
#include <SDL_ttf.h>

class Texture
{
private:
	struct TextureRef
	{
		SDL_Texture*			texture;
		int						count;

		TextureRef(SDL_Texture* tex) : texture(tex), count(1) {}
	};

	TextureRef*					m_texture;
	int							m_width;
	int							m_height;
	SDL_Surface*				m_surfacePixels;

public:
	Texture();
	Texture(const Texture& other);
	Texture(Texture&& other) noexcept;
	Texture& operator=(const Texture& other);
	Texture& operator=(Texture&& other) noexcept;
	~Texture();

	bool loadPixelsFromFile(const char* path);
	bool loadFromPixels(const bool flag, const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha);
	bool loadFromFile(const char* path, const bool flag, const Uint8 red = 0xFF, const Uint8 green = 0xFF, const Uint8 blue = 0xFF, const Uint8 alpha = 0xFF);
	bool loadFromRenderedText(const char* text, TTF_Font* font, SDL_Color textColor);

	void render(int x, int y, SDL_Rect* clip = nullptr, int scaleW = 0, int scaleH = 0, double angle = 0.0, SDL_Point* centre = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void resize(int width, int height);
	void free();
	void swap(TextureRef*& first, TextureRef*& second) noexcept;

	SDL_Texture* getTexture();
	int getWidth();
	int getHeight();
};

#endif // !TEXTURE_H