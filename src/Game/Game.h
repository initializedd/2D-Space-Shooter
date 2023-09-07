#ifndef GAME_H
#define GAME_H

#include "../Window/Window.h"
#include "../Resource/Texture/Texture.h"
#include "../Resource/Sound/Sound.h"
#include "../Menu/MainMenu/MainMenu.h"
#include "../Menu/CustomiseMenu/CustomiseMenu.h"
#include "../Entity/Player/Player.h"
#include "../Wave/Wave.h"
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