#include "Texture.h"
#include "SDL_image.h"
#include "Globals.h"
#include "Constants.h"
#include <cstdio>

Texture::Texture()
	: m_texture{}
	, m_width{}
	, m_height{}
	, m_surfacePixels{}
{
}

Texture::~Texture()
{
	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
}

bool Texture::loadPixelsFromFile(const char* path)
{
	SDL_Surface* loadedSurface{ IMG_Load(path) };
	if (!loadedSurface)
	{
		printf("Failed to load surface, Error: %s\n", IMG_GetError());
		return false;
	}
	else
	{
		m_surfacePixels = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_ABGR8888, 0);
		if (!m_surfacePixels)
		{
			printf("Failed to convert surface format, Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			m_width = m_surfacePixels->w;
			m_height = m_surfacePixels->h;
		}

		SDL_FreeSurface(loadedSurface);
		loadedSurface = nullptr;
	}

	return true;
}

bool Texture::loadFromPixels(const bool flag, const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha)
{
	if (!m_surfacePixels)
	{
		printf("No pixels loaded\n");
		return false;
	}
	else
	{
		SDL_SetColorKey(m_surfacePixels, flag, SDL_MapRGBA(m_surfacePixels->format, red, green, blue, alpha));
		
		m_texture = SDL_CreateTextureFromSurface(gWindow.getRenderer(), m_surfacePixels);
		if (!m_texture)
		{
			printf("Failed to create texture from surface, Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			m_width = m_surfacePixels->w;
			m_height = m_surfacePixels->h;
		}

		SDL_FreeSurface(m_surfacePixels);
		m_surfacePixels = nullptr;
	}

	return true;
}

bool Texture::loadFromFile(const char* path, const bool flag, const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha)
{
	if (!loadPixelsFromFile(path))
	{
		printf("Failed to load pixels from file path: %s\n", path);
		return false;
	}
	else
	{
		if (!loadFromPixels(flag, red, green, blue, alpha))
		{
			printf("Failed to load from pixels\n");
			return false;
		}
	}

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

	SDL_RenderCopyEx(gWindow.getRenderer(), m_texture, clip, &render_quad, angle, centre, flip);
}

void Texture::resize(int width, int height)
{
	m_width = width;
	m_height = height;
}

int Texture::getWidth()
{
	return m_width;
}
int Texture::getHeight()
{
	return m_height;
}

void Texture::free()
{
	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
}