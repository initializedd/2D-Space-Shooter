#include "Game.h"
#include "../Common/Common.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

// sdl
// img
// mix
// ttf

Game::Game()
{
}

Game::~Game()
{
}

bool Game::init()
{

	return true;
}

bool Game::load()
{
	mainMenu->createButtons();
	customiseMenu->createButtons();
	optionsMenu->createButtons();

	return true;
}

void Game::loop()
{
	bool quitGame = false;

	SDL_Event eventMenu;
	bool quitMenu = false;

	activeMenu = mainMenu;
	while (!activeMenu->isQuit())
	{
		activeMenu->displayMenu(eventMenu, quitGame);
	}

	SDL_Event event;


	resourceManager.getSoundSystem().findSound("sfx_game")->playChunk(-1, -1, 50);

	int countedFrames = 0;

	SDL_Color textColor{ 0x00, 0xFF, 0x00, 0xFF };

	gEnts.push_back(std::move(gPlayer));

	Timer deltaTimer;
	double fixedDt = 1.0 / 60.0;
	double accumulator = 0.0;

	Timer fpsTimer;
	fpsTimer.start();

	{
		PickUp pickUp{};
		pickUp.createItem(UPGRADE_SHIELD);
		gPickUp.push_back(pickUp);
	}

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
		}

		for (int i = 0; i < gEnts.size(); ++i)
		{
			gEnts[i]->handleKeyboardInputs();
		}

		resourceManager.getRenderSystem().getWindow().calculateFPS(fpsTimer, countedFrames);

		gWave.createWave();

		while (accumulator >= fixedDt)
		{
			// Update Entity
			for (int i = 0; i < gEnts.size(); ++i)
			{
				gEnts[i]->update(i, fixedDt);
			}

			for (int i = 0; i < gPickUp.size(); ++i)
			{
				gPickUp[i].update(fixedDt);
			}

			accumulator -= fixedDt;
		}

		render();

		++countedFrames;
	}
}

void Game::update()
{

}

void Game::render()
{
	// Rendering
	SDL_SetRenderDrawColor(resourceManager.getRenderSystem().getWindow().getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(resourceManager.getRenderSystem().getWindow().getRenderer());

	resourceManager.getTextureSystem().findTexture("tex_game_background")->render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr);

	for (int i = 0; i < gEnts.size(); ++i)
	{
		gEnts[i]->render();

		#if defined(_DEBUG)
		gEnts[i]->debug();
		#endif			
	}

	for (int i = 0; i < gPickUp.size(); ++i)
	{
		gPickUp[i].render();
	}

	gWave.displayWaveNum();

	std::shared_ptr<Text> fpsText = resourceManager.getTextSystem().findTextStream("txt_fps");

	fpsText->getTexture()->render(SCREEN_WIDTH - fpsText->getTexture()->getWidth() * sf.x, 0, fpsText->getTexture()->getWidth() * sf.x, fpsText->getTexture()->getHeight() * sf.y, nullptr);

	SDL_RenderPresent(resourceManager.getRenderSystem().getWindow().getRenderer());
}