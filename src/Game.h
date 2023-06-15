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