#include "Window.h"
#include "Menu.h"
#include "Texture.h"
#include "Timer.h"
#include "Wave.h"
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
	if (!gShipsSprite.loadFromFile("img/ships_sprite.png", false))
		return false;

	gShipsSprite.setClipsFromSprite(128, 160, 40, 48);

	if (!gBackgroundTexture.loadFromFile("img/space_bg.png", false))
		return false;

	gBackgroundTexture.scale(SCREEN_WIDTH, SCREEN_HEIGHT);

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

	if (!gProjectileTexture.loadFromFile("img/bullet.png", false))
		return false;

	if (!gExhaustParticle.getTexture().loadFromFile("img/fire_sprite.png", false))
		return false;

	gExhaustParticle.setClipsFromSprite(400, 400, 40, 6);

	if (!gExplosionParticle.getTexture().loadFromFile("img/explosion_sprite.png", false))
		return false;

	gExplosionParticle.setClipsFromSprite(96, 96, 40, 12);
	gExplosionParticle.getTexture().scale(96, 96);

	if (!gProjectileSound.loadChunk("audio/new laser.mp3"))
		return false;

	if (!gExplosionSound.loadChunk("audio/explosion.wav"))
		return false;

	if (!gPlayer->getParticle().getTexture().loadFromFile("img/fire_sprite.png", false))
		return false;

	gPlayer->getParticle().setClipsFromSprite(400, 400, 40, 6);
	gPlayer->getParticle().getTexture().scale(400 * 0.05, 400 * 0.05);

	gFuturaFont = TTF_OpenFont("font/futura.ttf", 28);
	if (!gFuturaFont)
	{
		printf("Failed to open font, Error: %s\n", TTF_GetError());
		return false;
	}

	/*if (!gEnemyTexture.loadFromFile("img/enemy_ship1.png", false))
		return false;
	gEnemyTexture.scale(gEnemyTexture.getWidth() * 0.4, gEnemyTexture.getHeight() * 0.4);*/

	//gPlayer->setColliders();

	return true;
}

void free()
{
	for (int i = 0; i < gEnts.size(); ++i)
	{
		if (gEnts[i])
		{
			delete gEnts[i];
			gEnts.erase(gEnts.begin() + i);
		}
	}

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
			bool quitGame = false;

			SDL_Event eventMenu;
			bool quitMenu = false;

			/*Menu mainMenu{};
			mainMenu.getTexture().loadFromFile("img/mainmenu_bg.jpg", false);
			mainMenu.getTexture().scale(SCREEN_WIDTH, SCREEN_HEIGHT);

			for (int i = PLAY; i < MAIN_TOTAL_BUTTONS; ++i)
			{
				Button button{};

				button.createButton(static_cast<MainMenuButtons>(i), gFuturaFont, SDL_Color(0xFF, 0xFF, 0xFF, 0xFF));
				mainMenu.getButtons().push_back(button);
			}*/

			Menu customiseMenu{};
			customiseMenu.getTexture().loadFromFile("img/mainmenu_bg.jpg", false);
			customiseMenu.getTexture().scale(SCREEN_WIDTH, SCREEN_HEIGHT);

			for (int i = BACK; i < CUSTOMISE_TOTAL_BUTTONS; ++i)
			{
				Button button{};

				button.createButton(static_cast<CustomiseMenuButtons>(i), gFuturaFont, SDL_Color(0xFF, 0xFF, 0xFF, 0xFF));
				customiseMenu.getButtons().push_back(button);
			}

			while (!customiseMenu.isQuit())
			{
				customiseMenu.displayMenu(eventMenu, quitGame);
			}



			/*while (!mainMenu.isQuit())
			{
				mainMenu.displayMenu(eventMenu, quitGame);
			}*/

			SDL_Event event;

			/*Sound backgroundMusic{};
			backgroundMusic.loadMusic("audio/Orbital Colossus.mp3");
			backgroundMusic.playMusic(-1);
			Mix_VolumeMusic(10);*/

			int countedFrames = 0;

			SDL_Color textColor{ 0x00, 0xFF, 0x00, 0xFF };

			gEnts.push_back(gPlayer);

			Timer deltaTimer;
			double fixedDt = 1.0 / 60.0;
			double accumulator = 0.0;

			Timer fpsTimer;
			fpsTimer.start();

			while (!quitGame)
			{
				double frameTime = deltaTimer.getTicks() / 1000.0;
				if (frameTime > 0.25)
					frameTime = 0.25;

				accumulator += frameTime;
				deltaTimer.start();

				while (SDL_PollEvent(&event) != 0)
				{
					if (event.type == SDL_QUIT)
					{
						quitGame = true;
					}

					for (int i = 0; i < gEnts.size(); ++i)
					{
						gEnts[i]->handleEvent(event);
					}
				}

				gWindow.calculateFPS(fpsTimer, countedFrames);

				if (!gFpsTextTexture.loadFromRenderedText(gWindow.getFPS().str().c_str(), gFuturaFont, textColor))
					return false;

				gWave.createWave();

				while (accumulator >= fixedDt)
				{
					// Update Entity
					for (int i = 0; i < gEnts.size(); ++i)
					{
						gEnts[i]->update(i, fixedDt);
					}

					accumulator -= fixedDt;
				}

				// Rendering
				SDL_SetRenderDrawColor(gWindow.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gWindow.getRenderer());

				gBackgroundTexture.render(0, 0);

				SDL_SetRenderDrawColor(gWindow.getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
				for (int i = 0; i < gEnts.size(); ++i)
				{
					gEnts[i]->render();

					#if defined(_DEBUG)
					gEnts[i]->debug();
					#endif			
				}

				if (gWave.displayWaveNum())
					gWave.getWaveTexture().render(0, SCREEN_HEIGHT - 74);
				else
					break;

				gFpsTextTexture.render(SCREEN_WIDTH - gFpsTextTexture.getWidth(), 0);

				SDL_RenderPresent(gWindow.getRenderer());

				++countedFrames;
			}
		}
	}

	free();

	return 0;
}