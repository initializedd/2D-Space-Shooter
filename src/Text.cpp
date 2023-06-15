#include "Text.h"
#include <cstdio>

Text::Text()
	: m_texture{}
{
}

bool Text::loadFromText(const std::string& text, TTF_Font* font, const SDL_Color& color)
{
	if (!m_texture.loadFromRenderedText(text, font, color))
		return false;

	return true;
}

Texture* Text::getTexture()
{
	return &m_texture;
}