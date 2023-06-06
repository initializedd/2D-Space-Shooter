#include "SoundSystem.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <cstdio>

SoundSystem::SoundSystem()
{
}

bool SoundSystem::init()
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf("Failed to initialize SDL_INIT_AUDIO, Error: %s\n", SDL_GetError());
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("Failed to initialize Mixer, Error: %s\n", Mix_GetError());
		return false;
	}

	Mix_AllocateChannels(20);
}

void SoundSystem::free()
{
	Mix_Quit();
}