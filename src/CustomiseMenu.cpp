#include "CustomiseMenu.h"
#include "Constants.h"
#include "Globals.h"

CustomiseMenu::CustomiseMenu()
{
	m_backgroundTexture.loadFromFile("img/mainmenu_bg.jpg", false);
	m_backgroundTexture.scale(SCREEN_WIDTH, SCREEN_HEIGHT);

	createButtons();
}

void CustomiseMenu::createButtons()
{
	m_buttons = { Button(BACK,		"Back",		gFuturaFont, SDL_Color(0xFF, 0xFF, 0xFF, 0xFF), SDL_Rect(0, 0, 200, 50)),
				  Button(LEFT,		"Left",		gFuturaFont, SDL_Color(0xFF, 0xFF, 0xFF, 0xFF), SDL_Rect(0, (SCREEN_HEIGHT / 2) - 20, 200, 50)),
				  Button(RIGHT,		"Right",	gFuturaFont, SDL_Color(0xFF, 0xFF, 0xFF, 0xFF), SDL_Rect(440, (SCREEN_HEIGHT / 2) - 20, 200, 50)),
				  Button(SELECT,	"Select",	gFuturaFont, SDL_Color(0xFF, 0xFF, 0xFF, 0xFF), SDL_Rect(220, 430, 200, 50)) };
}

void CustomiseMenu::displayMenu(SDL_Event& event, bool& quitGame)
{
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
						m_exitMenu = true;
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