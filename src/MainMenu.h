#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Menu.h"

class MainMenu : public Menu
{
private:

public:
	MainMenu();

	void createButtons();
	void displayMenu(SDL_Event& event, bool& quitGame);
};

#endif // !MAIN_MENU_H