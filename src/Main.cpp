#include "Game.h"
#include "Common.h"

int main(int argc, char* argv[])
{
	gPlayer = std::make_unique<Player>(100, 100);

	resourceManager.loadDatabase("../../../src/resourcedata.bin");

	Game game{};
	
	if (game.init())
	{
		if (game.load())
		{
			game.loop();
		}
	}

	delete mainMenu;
	delete customiseMenu;

	return 0;
}