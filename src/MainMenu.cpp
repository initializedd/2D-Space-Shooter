#include "MainMenu.h"
#include "Common.h"
#include <memory>
#include "Random.h"

MainMenu::MainMenu()
{
}

void MainMenu::createButtons()
{
	m_buttons.emplace_back(Button(PLAY,			SDL_Rect(200, 100, 200, 50)));
	m_buttons.emplace_back(Button(CUSTOMISE,	SDL_Rect(200, 175, 200, 50)));
	m_buttons.emplace_back(Button(OPTIONS,		SDL_Rect(200, 250, 200, 50)));
}

void MainMenu::displayMenu(SDL_Event& event, bool& quitGame)
{
	std::shared_ptr<Texture> texture = resourceManager.getTextureSystem().findTexture("tex_main_menu");

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			m_exitMenu = true;
			quitGame = true;
		}

		for (int i = 0; i < m_buttons.size(); ++i)
		{
			m_buttons[i].handleEvent(event);

			if (m_buttons[i].isSelected())
			{
				switch (m_buttons[i].getType())
				{
					case PLAY:
						if (!gPlayer)
							gPlayer = std::make_unique<Player>(100 * sf.x, 100 * sf.y);

						if (!gPlayer->hasSelectedShip())
						{
							int num = getRandomNumber(0, 47);
							gPlayer->getShip().createShip(num);
						}

						m_exitMenu = true;
						break;

					case CUSTOMISE:
						activeMenu = customiseMenu;
						break;

					case OPTIONS:
						activeMenu = optionsMenu;
						break;
				}
			}
		}
	}

	SDL_SetRenderDrawColor(resourceManager.getRenderSystem().getWindow().getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(resourceManager.getRenderSystem().getWindow().getRenderer());

	texture->render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr);

	for (int i = 0; i < m_buttons.size(); ++i)
	{
		m_buttons[i].renderButton();
	}

	SDL_RenderPresent(resourceManager.getRenderSystem().getWindow().getRenderer());
}