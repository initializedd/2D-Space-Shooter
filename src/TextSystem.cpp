#include "TextSystem.h"
#include <SDL_ttf.h>
#include <cstdio>

TextSystem::TextSystem()
{
}

bool TextSystem::init()
{
	if (TTF_Init() < 0)
	{
		printf("Failed to initialize TTF, Error: %s\n", TTF_GetError());
		return false;
	}
}

void TextSystem::free()
{
	//TTF_CloseFont(m_futuraFont);
	//m_futuraFont = nullptr;

	TTF_Quit();
}