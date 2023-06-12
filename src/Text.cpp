#include "Text.h"
#include <cstdio>

Text::Text()
	: m_font{}
	, m_texture{}
	, m_textStream{}
{
}

Text::~Text()
{
	if (m_font)
		TTF_CloseFont(m_font);
}

bool Text::loadFont(const std::string& path)
{
	m_font = TTF_OpenFont(path.c_str(), 28);
	if (!m_font)
	{
		printf("Failed to open font, Error: %s\n", TTF_GetError());
		return false;
	}

	return true;
}

bool Text::loadTextTexture(const std::string& text)
{
	if (!m_texture.loadFromRenderedText(text, m_font, SDL_Color(0xFF, 0xFF, 0xFF, 0xFF)))
		return false;

	return true;
}

bool Text::loadFromTextStream(const std::stringstream& text)
{
	if (!m_texture.loadFromRenderedText(text.str().c_str(), m_font, SDL_Color(0xFF, 0xFF, 0xFF, 0xFF)))
		return false;

	return true;
}

TTF_Font* Text::getFont() const
{
	return m_font;
}

Texture* Text::getTexture()
{
	return &m_texture;
}