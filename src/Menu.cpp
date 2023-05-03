#include "Menu.h"
#include "Window.h"
#include "Globals.h"

Menu::Menu()
	: m_buttons{}
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
				m_quit = true;
		}
	}

	SDL_SetRenderDrawColor(gWindow.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gWindow.getRenderer());

	gMainMenuTexture.render(0, 0);

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

std::vector<Button>& Menu::getButtons()
{
	return m_buttons;
}