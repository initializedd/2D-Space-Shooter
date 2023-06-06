#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "Texture.h"
#include "Sound.h"
#include "MainMenu.h"
#include "CustomiseMenu.h"
#include "Player.h"
#include "Wave.h"
#include <vector>
#include <memory>
#include <SDL_rect.h>

class Game
{
private:
	Window										m_window;
	Texture										m_backgroundTexture;
	Texture										m_fpsTextTexture;

	std::shared_ptr<Texture>					m_shipsSprite;
	Texture										m_projectileTexture;

	Texture										m_exhaustTexture;
	Texture										m_explosionTexture;

	std::shared_ptr<Texture>					m_upgradesSprite;

	Sound										m_backgroundMusic;
	Sound										m_projectileSound;
	Sound										m_explosionSound;

	Player*										m_player;

	TTF_Font*									m_futuraFont;

	Menu*										m_activeMenu;
	MainMenu*									m_mainMenu;
	CustomiseMenu*								m_customiseMenu;

	std::vector<Entity*>						m_entities;
	Wave										m_wave;

	std::vector<std::unique_ptr<PickUp>>		m_pickups;

public:
	Game();
	~Game();

	bool init();
	bool load();
	void loop();

	void update();
	void render();
};

#endif // !GAME_H