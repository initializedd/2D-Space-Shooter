#include "Window.h"
#include "Texture.h"
#include "Timer.h"
#include "Globals.h"
#include "Constants.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cstdio>
#include <sstream>

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("Failed to initialize SDL, Error: %s\n", SDL_GetError());
		return false;
	}

	if (!gWindow.createWindow())
		return false;

	if (!gWindow.createRenderer())
		return false;

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		printf("Failed to initialize IMG, Error: %s\n", IMG_GetError());
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("Failed to initialize Mixer, Error: %s\n", Mix_GetError());
		return false;
	}

	if (TTF_Init() == -1)
	{
		printf("Failed to initialize TTF, Error: %s\n", TTF_GetError());
		return false;
	}

	return true;
}

bool loadMedia()
{
	if (!gBackgroundTexture.loadFromFile("img/space_bg.png", false))
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

	if (!gPlayer.getTexture().loadFromFile("img/spiked_ship.png", false))
		return false;

	if (!gProjectileTexture.loadFromFile("img/bullet.png", false))
		return false;

	if (!gLaserSound.loadChunk("audio/new laser.mp3"))
		return false;

	if (!gPlayer.getParticle().getTexture().loadFromFile("img/fire_sprite.png", false))
		return false;

	gPlayer.getParticle().setClipsFromSprite(400, 400, 20);
	gPlayer.getParticle().getTexture().resize(gPlayer.getParticle().getTexture().getWidth() * 0.015, gPlayer.getParticle().getTexture().getHeight() * 0.015);

	gFuturaFont = TTF_OpenFont("font/futura.ttf", 28);
	if (!gFuturaFont)
	{
		printf("Failed to open font, Error: %s\n", TTF_GetError());
		return false;
	}

	if (!gEnemy.getTexture().loadFromFile("img/enemy_ship1.png", false))
		return false;

	gPlayer.setColliders();

	gEnemy.getTexture().resize(gEnemy.getTexture().getWidth() * 0.4, gEnemy.getTexture().getHeight() * 0.4);
	gEnemy.setCollider();

	return true;
}

void free()
{
	SDL_FreeSurface(gWindowIconTexture);
	gWindowIconTexture = nullptr;

	TTF_CloseFont(gFuturaFont);
	gFuturaFont = nullptr;

	TTF_Quit();
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

			/*Sound backgroundMusic{};
			backgroundMusic.loadMusic("audio/Orbital Colossus.mp3");
			backgroundMusic.playMusic(-1);
			Mix_VolumeMusic(15);*/

			int countedFrames = 0;
			int flameFrames = 0;

			Timer fpsTimer;
			fpsTimer.start();

			SDL_Color textColor{ 0x00, 0xFF, 0x00, 0xFF };

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

				gWindow.calculateFPS(fpsTimer, countedFrames);

				if (!gFpsTextTexture.loadFromRenderedText(gWindow.getFPS().str().c_str(), textColor))
					return false;

				SDL_SetRenderDrawColor(gWindow.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gWindow.getRenderer());

				gBackgroundTexture.render(0, 0);

				gPlayer.animateExhaust(flameFrames);

				gPlayer.getTexture().render(gPlayer.getPosX(), gPlayer.getPosY());

				gEnemy.getTexture().render(gEnemy.getPosX(), gEnemy.getPosY(), nullptr, 0, 0, 180);

				// Debug
				SDL_SetRenderDrawColor(gWindow.getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
				SDL_RenderDrawRect(gWindow.getRenderer(), &gPlayer.getColliders().at(0));
				SDL_RenderDrawRect(gWindow.getRenderer(), &gPlayer.getColliders().at(1));
				SDL_RenderDrawRect(gWindow.getRenderer(), &gPlayer.getColliders().at(2));
				SDL_RenderDrawRect(gWindow.getRenderer(), &gPlayer.getColliders().at(3));
				SDL_RenderDrawRect(gWindow.getRenderer(), &gPlayer.getColliders().at(4));
				SDL_RenderDrawRect(gWindow.getRenderer(), &gPlayer.getColliders().at(5));

				// Debug
				SDL_SetRenderDrawColor(gWindow.getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
				SDL_RenderDrawRect(gWindow.getRenderer(), &gEnemy.getColliders().at(0));
				SDL_RenderDrawRect(gWindow.getRenderer(), &gEnemy.getColliders().at(1));

				gPlayer.getWeapon().updateProjectiles();

				gFpsTextTexture.render(SCREEN_WIDTH - gFpsTextTexture.getWidth(), 0);

				SDL_RenderPresent(gWindow.getRenderer());

				++flameFrames;
				if (flameFrames / 6 >= 6)
				{
					flameFrames = 0;
				}

				++countedFrames;
			}
		}
	}

	free();

	return 0;
}