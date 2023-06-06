#include "RenderSystem.h"
#include <SDL.h>
#include <cstdio>

RenderSystem::RenderSystem()
	: m_window{}
{
}

bool RenderSystem::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Failed to initialize SDL_INIT_VIDEO, Error: %s\n", SDL_GetError());
		return false;
	}

	if (!m_window.createWindow())
		return false;

	if (!m_window.createRenderer())
		return false;

	return true;
}

void RenderSystem::free()
{
	SDL_Quit();
}