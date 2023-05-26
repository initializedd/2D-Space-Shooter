#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Menu.h"

class MainMenu : public Menu
{
private:
	void createButtons();

public:
	MainMenu();

	void displayMenu(SDL_Event& event, bool& quitGame);
};

#endif // !MAIN_MENU_H