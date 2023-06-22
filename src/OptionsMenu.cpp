#include "OptionsMenu.h"
#include "Common.h"

OptionsMenu::OptionsMenu()
{
}

void OptionsMenu::createButtons()
{
	m_buttons.emplace_back(Button(BACK,			SDL_Rect(0, 0, 200, 50)));
	m_buttons.emplace_back(Button(RESOLUTION,	SDL_Rect(200, 175, 200, 50)));
	m_buttons.emplace_back(Button(OPTIONS,		SDL_Rect(200, 250, 200, 50)));
}

void OptionsMenu::displayMenu(SDL_Event& event, bool& quitGame)
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
					case BACK:
						activeMenu = mainMenu;
						break;

					case RESOLUTION:
						sf.x = 1920.0 / 640.0;
						sf.y = 1080.0 / 480.0;
						SCREEN_WIDTH = 1920;
						SCREEN_HEIGHT = 1080;
						resourceManager.getRenderSystem().getWindow().resizeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
						break;

					case OPTIONS:
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