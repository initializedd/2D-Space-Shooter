#include "Menu.h"
#include "Window.h"
#include "Globals.h"

Menu::Menu()
	: m_backgroundTexture{}
	, m_buttons{}
	, m_quit{}
{
}

Menu::~Menu()
{

}

void Menu::displayMenu(SDL_Event& event, bool& quitGame)
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			m_quit = true;
			quitGame = true;
		}

		for (int i = 0; i < m_buttons.size(); ++i)
		{
			m_buttons[i].handleEvent(event);

			if (m_buttons[i].isSelected())
			{
				switch (m_buttons[i].getCustomiseType())
				{
					case BACK:
						m_quit = true;
						break;

					case LEFT:
						if (gShipsSprite.getIndex() <= 0)
							gShipsSprite.setIndex(47);
						else
							gShipsSprite.setIndex(gShipsSprite.getIndex() - 1);
						break;

					case RIGHT:
						if (gShipsSprite.getIndex() >= 47)
							gShipsSprite.setIndex(0);
						else
							gShipsSprite.setIndex(gShipsSprite.getIndex() + 1);
						break;

					case SELECT:
						gPlayer->getShip().getTexture().setTexture(gShipsSprite);
						gPlayer->getShip().createShip(gShipsSprite.getIndex());
						break;
				}
			}
		}
	}

	SDL_SetRenderDrawColor(gWindow.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gWindow.getRenderer());

	m_backgroundTexture.render(0, 0);
	gShipsSprite.render((SCREEN_WIDTH / 2) - (gShipsSprite.getClips()[gShipsSprite.getIndex()].w / 2), (SCREEN_HEIGHT / 2) - (gShipsSprite.getClips()[gShipsSprite.getIndex()].h / 2), &gShipsSprite.getClips()[gShipsSprite.getIndex()], gShipsSprite.getClips()[gShipsSprite.getIndex()].w, gShipsSprite.getClips()[gShipsSprite.getIndex()].h);

	for (int i = 0; i < m_buttons.size(); ++i)
	{
		m_buttons[i].renderButton();
	}

	SDL_RenderPresent(gWindow.getRenderer());
}

bool Menu::isQuit()
{
	return m_quit;
}

Texture& Menu::getTexture()
{
	return m_backgroundTexture;
}

std::vector<Button>& Menu::getButtons()
{
	return m_buttons;
}