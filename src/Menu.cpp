#include "Menu.h"
#include "Window.h"
#include "Globals.h"

Menu::Menu()
	: m_button{}
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

		m_button.handleEvent(event);

		if (m_button.isSelected())
			m_quit = true;
	}

	SDL_SetRenderDrawColor(gWindow.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gWindow.getRenderer());

	gMainMenuTexture.render(0, 0);

	m_button.renderButton();

	SDL_RenderPresent(gWindow.getRenderer());
}

Button& Menu::getButton()
{
	return m_button;
}

bool Menu::isQuit()
{
	return m_quit;
}