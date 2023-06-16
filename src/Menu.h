#ifndef MENU_H
#define MENU_H

#include "Texture.h"
#include "Button.h"
#include <vector>
#include <memory>

class Menu
{
protected:
	Texture										m_backgroundTexture;
	std::vector<Button>							m_buttons;
	bool										m_exitMenu;

public:
	Menu();

	virtual void displayMenu(SDL_Event& event, bool& quitGame) = 0;

	bool isQuit();

	Texture& getTexture();
	std::vector<Button>& getButtons();
};

#endif // !MENU_H