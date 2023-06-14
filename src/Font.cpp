#include "Font.h"

Font::Font()
	: m_font{}
	, m_ptsize{}
{
}

Font::~Font()
{
	if (m_font)
		TTF_CloseFont(m_font);
}

bool Font::loadFont(const std::string& path, int ptsize)
{
	m_font = TTF_OpenFont(path.c_str(), ptsize);
	if (!m_font)
	{
		printf("Failed to open font, Error: %s\n", TTF_GetError());
		return false;
	}

	return true;
}

TTF_Font* Font::getFont()
{
	return m_font;
}