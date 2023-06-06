#include "TextureSystem.h"
#include <SDL_image.h>
#include <cstdio>

TextureSystem::TextureSystem()
{
}

bool TextureSystem::init()
{
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		printf("Failed to initialize IMG, Error: %s\n", IMG_GetError());
		return false;
	}
}

void TextureSystem::free()
{
	IMG_Quit();
}