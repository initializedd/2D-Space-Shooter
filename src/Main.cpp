#include "Game.h"
#include "Common.h"

int main(int argc, char* argv[])
{
	resourceManager.loadDatabase("../../../resources/resourcedata.bin");

	Game game{};
	
	if (game.init())
	{
		if (game.load())
		{
			game.loop();
		}
	}

	return 0;
}