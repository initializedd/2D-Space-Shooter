#include "Window.h"
#include "Texture.h"
#include "Globals.h"
#include "Constants.h"
#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
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

	return true;
}

void free()
{
	SDL_FreeSurface(gWindowIconTexture);
	gWindowIconTexture = nullptr;

	gProjectileTexture.free();
	gPlayer.getTexture().free();
	gBackgroundTexture.free();

	gWindow.free();

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

				gPlayer.getTexture().render(gPlayer.getPosX(), gPlayer.getPosY());

				gPlayer.getWeapon().updateProjectiles();

				SDL_RenderPresent(gWindow.getRenderer());
			}
		}
	}

	free();

	return 0;
}