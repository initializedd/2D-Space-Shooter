#include "Window.h"
#include "Texture.h"
#include "Globals.h"
#include "Constants.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <cstdio>

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("Failed to initialize SDL, Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		if (!gWindow.createWindow())
			return false;
		else
		{
			if (!gWindow.createRenderer())
				return false;

			if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
			{
				printf("Failed to initialize IMG, Error: %s\n", IMG_GetError());
				return false;
			}
			else
			{
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("Failed to initialize Mixer, Error: %s\n", Mix_GetError());
					return false;
				}
			}
		}
	}

	return true;
}

bool loadMedia()
{
	if (!gBackgroundTexture.loadFromFile("img/space.png", false))
		return false;

	gBackgroundTexture.resize(SCREEN_WIDTH, SCREEN_HEIGHT);

	gWindowIconTexture = IMG_Load("img/spaceship.png");
	if (!gWindowIconTexture)
	{
		printf("Failed to load surface, Error: %s\n", IMG_GetError());
		return false;
	}
	else
	{
		SDL_SetWindowIcon(gWindow.getWindow(), gWindowIconTexture);
	}

	if (!gPlayer.setTexture("img/spiked_ship.png", false))
		return false;

	if (!gProjectileTexture.loadFromFile("img/bullet.png", false))
		return false;

	if (!gLaserSound.loadChunk("audio/new laser.mp3"))
		return false;

	if (!gFlameTexture.loadFromFile("img/fire_sprite.png", false))
		return false;

	gFlameTexture.resize(gFlameTexture.getWidth() * 0.015, gFlameTexture.getHeight() * 0.015);

	gFlameClips[0].x = 10;
	gFlameClips[0].y = 10;
	gFlameClips[0].w = 400;
	gFlameClips[0].h = 400;

	gFlameClips[1].x = 430;
	gFlameClips[1].y = 10;
	gFlameClips[1].w = 400;
	gFlameClips[1].h = 400;

	gFlameClips[2].x = 10;
	gFlameClips[2].y = 430;
	gFlameClips[2].w = 400;
	gFlameClips[2].h = 400;

	gFlameClips[3].x = 430;
	gFlameClips[3].y = 430;
	gFlameClips[3].w = 400;
	gFlameClips[3].h = 400;

	gFlameClips[4].x = 850;
	gFlameClips[4].y = 10;
	gFlameClips[4].w = 400;
	gFlameClips[4].h = 400;

	gFlameClips[5].x = 850;
	gFlameClips[5].y = 430;
	gFlameClips[5].w = 400;
	gFlameClips[5].h = 400;

	return true;
}

void free()
{
	SDL_FreeSurface(gWindowIconTexture);
	gWindowIconTexture = nullptr;

	gFlameTexture.free();
	gProjectileTexture.free();
	gPlayer.getTexture().free();
	gBackgroundTexture.free();

	gWindow.free();

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	if (init())
	{
		if (loadMedia())
		{
			SDL_Event event;
			bool quit = false;

			Sound backgroundMusic{};
			backgroundMusic.loadMusic("audio/Orbital Colossus.mp3");
			backgroundMusic.playMusic(-1);
			Mix_VolumeMusic(15);

			int flameFrames = 0;

			while (!quit)
			{
				while (SDL_PollEvent(&event) != 0)
				{
					if (event.type == SDL_QUIT)
					{
						quit = true;
					}

					gPlayer.handleEvent(event);
				}

				gPlayer.move();

				SDL_SetRenderDrawColor(gWindow.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gWindow.getRenderer());

				gBackgroundTexture.render(0, 0);

				gPlayer.animateExhaust(flameFrames);

				gPlayer.getTexture().render(gPlayer.getPosX(), gPlayer.getPosY());

				gPlayer.getWeapon().updateProjectiles();

				SDL_RenderPresent(gWindow.getRenderer());

				++flameFrames;
				if (flameFrames / 6 >= 6)
				{
					flameFrames = 0;
				}
			}
		}
	}

	free();

	return 0;
}