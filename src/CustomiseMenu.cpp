#include "CustomiseMenu.h"
#include "Common.h"
#include "Game.h"

CustomiseMenu::CustomiseMenu()
	: m_index{}
{
}

void CustomiseMenu::createButtons()
{
	m_buttons.emplace_back(std::make_unique<Button>(BACK,	SDL_Rect(0, 0, 200, 50)));
	m_buttons.emplace_back(std::make_unique<Button>(LEFT,	SDL_Rect(0, (SCREEN_HEIGHT / 2) - 25, 200, 50)));
	m_buttons.emplace_back(std::make_unique<Button>(RIGHT,	SDL_Rect(440, (SCREEN_HEIGHT / 2) - 25, 200, 50)));
	m_buttons.emplace_back(std::make_unique<Button>(SELECT,	SDL_Rect(220, 430, 200, 50)));
}

void CustomiseMenu::displayMenu(SDL_Event& event, bool& quitGame)
{
	std::shared_ptr<Sprite> shipSprite = resourceManager.getTextureSystem().findSprite("sprite_ships");

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			m_exitMenu = true;
			quitGame = true;
		}
		
		for (int i = 0; i < m_buttons.size(); ++i)
		{
			m_buttons[i]->handleEvent(event);

			if (m_buttons[i]->isSelected())
			{
				switch (m_buttons[i]->getType())
				{
					case BACK:
						activeMenu = mainMenu;
						break;

					case LEFT:
						if (m_index <= 0)
							m_index = 47;
						else
							m_index -= 1;
						break;

					case RIGHT:
						if (m_index >= 47)
							m_index = 0;
						else
							m_index += 1;
						break;

					case SELECT:
						gPlayer->getShip().createShip(m_index);
						break;
				}
			}
		}
	}

	SDL_SetRenderDrawColor(resourceManager.getRenderSystem().getWindow().getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(resourceManager.getRenderSystem().getWindow().getRenderer());

	resourceManager.getTextureSystem().findTexture("tex_main_menu")->render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr);

	shipSprite->render
	(
		(SCREEN_WIDTH / 2) - (shipSprite->getClips()[m_index].w / 2), 
		(SCREEN_HEIGHT / 2) - (shipSprite->getClips()[m_index].h / 2), 
		shipSprite->getClips()[m_index].w,
		shipSprite->getClips()[m_index].h,
		&shipSprite->getClips()[m_index]
	);

	for (int i = 0; i < m_buttons.size(); ++i)
	{
		m_buttons[i]->renderButton();
	}

	SDL_RenderPresent(resourceManager.getRenderSystem().getWindow().getRenderer());
}