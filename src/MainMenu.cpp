#include "MainMenu.h"
#include "Constants.h"
#include "Globals.h"

MainMenu::MainMenu()
{
	m_backgroundTexture.loadFromFile("img/mainmenu_bg.jpg", false);
	m_backgroundTexture.scale(SCREEN_WIDTH, SCREEN_HEIGHT);

	createButtons();
}

void MainMenu::createButtons()
{
	m_buttons = { Button(PLAY,			"Play",			gFuturaFont, SDL_Color(0xFF, 0xFF, 0xFF, 0xFF), SDL_Rect(200, 100, 200, 50)),
				  Button(CUSTOMISE,		"Customise",	gFuturaFont, SDL_Color(0xFF, 0xFF, 0xFF, 0xFF), SDL_Rect(200, 175, 200, 50)),
				  Button(OPTIONS,		"Options",		gFuturaFont, SDL_Color(0xFF, 0xFF, 0xFF, 0xFF), SDL_Rect(200, 250, 200, 50)) };
}

void MainMenu::displayMenu(SDL_Event& event, bool& quitGame)
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
					case PLAY:
						m_exitMenu = true;
						break;

					case CUSTOMISE:
						break;

					case OPTIONS:
						break;
				}
			}
		}
	}

	SDL_SetRenderDrawColor(gWindow.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gWindow.getRenderer());

	m_backgroundTexture.render(0, 0);

	for (int i = 0; i < m_buttons.size(); ++i)
	{
		m_buttons[i].renderButton();
	}

	SDL_RenderPresent(gWindow.getRenderer());
}