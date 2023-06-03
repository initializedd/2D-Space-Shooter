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
	std::vector<std::unique_ptr<Button>>		m_buttons;
	bool										m_exitMenu;

public:
	Menu();

	virtual void displayMenu(SDL_Event& event, bool& quitGame) = 0;

	bool isQuit();

	Texture& getTexture();
	std::vector<std::unique_ptr<Button>>& getButtons();
};

#endif // !MENU_H