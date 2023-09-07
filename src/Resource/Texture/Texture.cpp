#include "Texture.h"
#include "../../Common/Common.h"
#include <SDL_image.h>
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

bool Texture::loadPixelsFromFile(const std::string& path)
{
	SDL_Surface* surface{ IMG_Load(path.c_str()) };
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

	m_texture = SDL_CreateTextureFromSurface(resourceManager.getRenderSystem().getWindow().getRenderer(), m_surfacePixels);
	if (!m_texture)
	{
		printf("Failed to create texture from surface, Error: %s\n", SDL_GetError());
		return false;
	}

	m_width = m_surfacePixels->w;
	m_height = m_surfacePixels->h;

	SDL_FreeSurface(m_surfacePixels);

	return true;
}

bool Texture::loadFromFile(const std::string& path, const bool flag, const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha)
{
	if (!loadPixelsFromFile(path))
	{
		printf("Failed to load pixels from file path: %s\n", path.c_str());
		return false;
	}

	if (!loadFromPixels(flag, red, green, blue, alpha))
	{
		printf("Failed to load from pixels\n");
		return false;
	}

	return true;
}

bool Texture::loadFromRenderedText(const std::string& text, TTF_Font* font, SDL_Color textColor)
{
	free();

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	if (!surface)
	{
		printf("Failed to render text solid to surface, Error: %s\n", TTF_GetError());
		return false;
	}

	m_texture = SDL_CreateTextureFromSurface(resourceManager.getRenderSystem().getWindow().getRenderer(), surface);
	if (!m_texture)
	{
		printf("Failed to create texture from surface, Error: %s\n", SDL_GetError());
		return false;
	}

	m_width = surface->w;
	m_height = surface->h;

	SDL_FreeSurface(surface);

	return true;
}

void Texture::render(int x, int y, int w, int h, SDL_Rect* srcrect, double angle, SDL_Point* centre, SDL_RendererFlip flip)
{
	SDL_Rect dstrect{ x, y, w, h};

	SDL_RenderCopyEx(resourceManager.getRenderSystem().getWindow().getRenderer(), m_texture, srcrect, &dstrect, angle, centre, flip);
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
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
}

SDL_Texture* Texture::getTexture()
{
	return m_texture;
}

int Texture::getWidth()
{
	return m_width;
}

int Texture::getHeight()
{
	return m_height;
}

void Texture::setTexture(Texture& texture)
{
	*this = texture;
}