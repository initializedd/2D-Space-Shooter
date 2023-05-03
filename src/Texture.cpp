#include "Texture.h"
#include "Globals.h"
#include "Constants.h"
#include <SDL_image.h>
#include <cstdio>

Texture::Texture()
	: m_texture{}
	, m_width{}
	, m_height{}
	, m_surfacePixels{}
{
}

Texture::Texture(const Texture& other)
	: m_texture{ other.m_texture }
	, m_width{ other.m_width }
	, m_height{ other.m_height }
	, m_surfacePixels{ other.m_surfacePixels }
{
	if (m_texture)
		++m_texture->count;
}

Texture::Texture(Texture&& other) noexcept
	: m_texture{}
{
	swap(m_texture, other.m_texture);
}

Texture& Texture::operator=(const Texture& other)
{
	if (this != &other)
	{
		if (m_texture && --m_texture->count == 0)
		{
			SDL_DestroyTexture(m_texture->texture);
			delete m_texture;
			m_texture = nullptr;
		}

		m_texture = other.m_texture;
		if (m_texture)
			++m_texture->count;
	}

	return *this;
}

Texture& Texture::operator=(Texture&& other) noexcept
{
	swap(m_texture, other.m_texture);

	return *this;
}

Texture::~Texture()
{
	if (m_texture)
	{
		if (--m_texture->count == 0)
		{
			SDL_DestroyTexture(m_texture->texture);
			delete m_texture;
			m_texture = nullptr;
		}
	}
}

bool Texture::loadPixelsFromFile(const char* path)
{
	SDL_Surface* surface{ IMG_Load(path) };
	if (!surface)
	{
		printf("Failed to load surface, Error: %s\n", IMG_GetError());
		return false;
	}

	m_surfacePixels = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ABGR8888, 0);
	if (!m_surfacePixels)
	{
		printf("Failed to convert surface format, Error: %s\n", SDL_GetError());
		return false;
	}

	m_width = m_surfacePixels->w;
	m_height = m_surfacePixels->h;

	SDL_FreeSurface(surface);

	return true;
}

bool Texture::loadFromPixels(const bool flag, const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha)
{
	if (!m_surfacePixels)
	{
		printf("No pixels loaded\n");
		return false;
	}

	SDL_SetColorKey(m_surfacePixels, flag, SDL_MapRGBA(m_surfacePixels->format, red, green, blue, alpha));

	SDL_Texture* texture = SDL_CreateTextureFromSurface(gWindow.getRenderer(), m_surfacePixels);
	if (!texture)
	{
		printf("Failed to create texture from surface, Error: %s\n", SDL_GetError());
		return false;
	}

	m_texture = new TextureRef(texture);
	if (!m_texture)
	{
		printf("Failed to create texture ref\n");
		return false;
	}

	m_width = m_surfacePixels->w;
	m_height = m_surfacePixels->h;

	SDL_FreeSurface(m_surfacePixels);

	return true;
}

bool Texture::loadFromFile(const char* path, const bool flag, const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha)
{
	if (!loadPixelsFromFile(path))
	{
		printf("Failed to load pixels from file path: %s\n", path);
		return false;
	}

	if (!loadFromPixels(flag, red, green, blue, alpha))
	{
		printf("Failed to load from pixels\n");
		return false;
	}

	return true;
}

bool Texture::loadFromRenderedText(const char* text, TTF_Font* font, SDL_Color textColor)
{
	free();

	SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
	if (!surface)
	{
		printf("Failed to render text solid to surface, Error: %s\n", TTF_GetError());
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(gWindow.getRenderer(), surface);
	if (!texture)
	{
		printf("Failed to create texture from surface, Error: %s\n", SDL_GetError());
		return false;
	}

	m_texture = new TextureRef(texture);
	if (!m_texture)
	{
		printf("Failed to create texture ref\n");
		return false;
	}

	m_width = surface->w;
	m_height = surface->h;

	SDL_FreeSurface(surface);

	return true;
}

void Texture::render(int x, int y, SDL_Rect* clip, int scaleW, int scaleH, double angle, SDL_Point* centre, SDL_RendererFlip flip)
{
	SDL_Rect render_quad{ x, y, m_width, m_height };

	if (clip)
	{
		render_quad.w = scaleW;
		render_quad.h = scaleH;
	}

	SDL_RenderCopyEx(gWindow.getRenderer(), m_texture->texture, clip, &render_quad, angle, centre, flip);
}

void Texture::scale(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Texture::free()
{
	if (m_texture)
	{
		if (--m_texture->count == 0)
		{
			SDL_DestroyTexture(m_texture->texture);
			delete m_texture;
			m_texture = nullptr;
		}
	}
}

void Texture::swap(TextureRef*& first, TextureRef*& second) noexcept
{
	TextureRef* temp = first;
	first = second;
	second = temp;
}

SDL_Texture* Texture::getTexture()
{
	return m_texture->texture;
}

int Texture::getWidth()
{
	return m_width;
}

int Texture::getHeight()
{
	return m_height;
}