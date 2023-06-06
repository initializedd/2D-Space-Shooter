#include "Game.h"
#include "Constants.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

// sdl
// img
// mix
// ttf

Game::Game()
	: m_window{}
	, m_backgroundTexture{}
	, m_fpsTextTexture{}
	, m_shipsSprite{}
	, m_projectileTexture{}
	, m_exhaustTexture{}
	, m_explosionTexture{}
	, m_upgradesSprite{}
	, m_backgroundMusic{}
	, m_projectileSound{}
	, m_explosionSound{}
	, m_player{}
	, m_futuraFont{}
	, m_activeMenu{}
	, m_mainMenu{}
	, m_customiseMenu{}
	, m_entities{}
	, m_wave{}
	, m_pickups{}
{
}

Game::~Game()
{
	delete m_mainMenu;
	delete m_customiseMenu;

	for (int i = 0; i < m_entities.size(); ++i)
	{
		if (m_entities[i])
		{
			delete m_entities[i];
			m_entities.erase(m_entities.begin() + i);
		}
	}
}

bool Game::init()
{

	if (!m_window.createWindow())
		return false;

	if (!m_window.createRenderer())
		return false;
	
	return true;
}

bool Game::load()
{
	if (!m_backgroundTexture.loadFromFile("img/space_bg.png", false))
		return false;

	if (!m_backgroundMusic.loadMusic("audio/Orbital Colossus.mp3"))
		return false;

	m_backgroundTexture.scale(SCREEN_WIDTH, SCREEN_HEIGHT);

	if (!m_shipsSprite->loadFromFile("img/ships_sprite.png", false))
		return false;

	m_shipsSprite->setClipsFromSprite(128, 160, 40, 48);


	if (!m_projectileTexture.loadFromFile("img/bullet.png", false))
		return false;

	if (!m_exhaustTexture.loadFromFile("img/fire_sprite.png", false))
		return false;

	m_exhaustTexture.setClipsFromSprite(400, 400, 40, 6);

	if (!m_explosionTexture.loadFromFile("img/explosion_sprite.png", false))
		return false;

	m_explosionTexture.setClipsFromSprite(96, 96, 40, 12);
	m_explosionTexture.scale(96, 96);

	if (!m_upgradesSprite->loadFromFile("img/upgrades_sprite.png", false))
		return false;

	m_upgradesSprite->setClipsFromSprite(250, 300, 40, 4);
	m_upgradesSprite->scale(m_upgradesSprite->getWidth() * 0.5, m_upgradesSprite->getHeight() * 0.5);

	if (!m_projectileSound.loadChunk("audio/new laser.mp3"))
		return false;

	if (!m_explosionSound.loadChunk("audio/explosion.wav"))
		return false;

	if (!m_player->getParticle().getTexture().loadFromFile("img/fire_sprite.png", false))
		return false;

	m_player->getParticle().setClipsFromSprite(400, 400, 40, 6);
	m_player->getParticle().getTexture().scale(400 * 0.05, 400 * 0.05);
	m_player->getUI().createUI();

	m_futuraFont = TTF_OpenFont("font/futura.ttf", 28);
	if (!m_futuraFont)
	{
		printf("Failed to open font, Error: %s\n", TTF_GetError());
		return false;
	}

	return true;
}

void Game::loop()
{
	bool quitGame = false;

	SDL_Event eventMenu;
	bool quitMenu = false;

	m_mainMenu = new MainMenu();
	m_customiseMenu = new CustomiseMenu();

	m_activeMenu = m_mainMenu;
	while (!m_activeMenu->isQuit())
	{
		m_activeMenu->displayMenu(eventMenu, quitGame);
	}

	SDL_Event event;

	m_backgroundMusic.playMusic(-1);
	Mix_VolumeMusic(50);

	int countedFrames = 0;

	SDL_Color textColor{ 0x00, 0xFF, 0x00, 0xFF };

	m_entities.push_back(m_player);

	Timer deltaTimer;
	double fixedDt = 1.0 / 60.0;
	double accumulator = 0.0;

	Timer fpsTimer;
	fpsTimer.start();

	{
		std::unique_ptr<PickUp> pickUp = std::make_unique<PickUp>();
		pickUp->createItem(UPGRADE_HEALTH);
		m_pickups.push_back(std::move(pickUp));
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

			for (int i = 0; i < m_entities.size(); ++i)
			{
				m_entities[i]->handleEvent(event);
			}
		}

		m_window.calculateFPS(fpsTimer, countedFrames);

		if (!m_fpsTextTexture.loadFromRenderedText(m_window.getFPS().str().c_str(), m_futuraFont, textColor))
			printf("Failed to load FPS texture, Error: %s\n", SDL_GetError());

		m_wave.createWave();

		while (accumulator >= fixedDt)
		{
			// Update Entity
			for (int i = 0; i < m_entities.size(); ++i)
			{
				m_entities[i]->update(i, fixedDt);
			}

			for (int i = 0; i < m_pickups.size(); ++i)
			{
				m_pickups[i]->update(fixedDt);
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
	SDL_SetRenderDrawColor(m_window.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(m_window.getRenderer());

	m_backgroundTexture.render(0, 0);

	for (int i = 0; i < m_entities.size(); ++i)
	{
		m_entities[i]->render();

		#if defined(_DEBUG)
		m_entities[i]->debug();
		#endif			
	}

	for (int i = 0; i < m_pickups.size(); ++i)
	{
		m_pickups[i]->render();
	}

	m_wave.displayWaveNum();

	m_fpsTextTexture.render(SCREEN_WIDTH - m_fpsTextTexture.getWidth(), 0);

	SDL_RenderPresent(m_window.getRenderer());
}

Window& Game::getWindow()
{
	return m_window;
}

TTF_Font* Game::getFuturaFont()
{
	return m_futuraFont;
}

Menu* Game::getActiveMenu()
{
	return m_activeMenu;
}

MainMenu* Game::getMainMenu()
{
	return m_mainMenu;
}

CustomiseMenu* Game::getCustomiseMenu()
{
	return m_customiseMenu;
}

std::shared_ptr<Texture> Game::getShipsSprite()
{
	return m_shipsSprite;
}

Player* Game::getPlayer()
{
	return m_player;
}

std::vector<Entity*>& Game::getEntities()
{
	return m_entities;
}

Texture& Game::getExhaustTexture()
{
	return m_exhaustTexture;
}

Texture& Game::getExplosionTexture()
{
	return m_explosionTexture;
}

void Game::setActiveMenu(Menu* menu)
{
	m_activeMenu = menu;
}