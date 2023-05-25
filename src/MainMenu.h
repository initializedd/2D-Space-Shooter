#ifndef MAINMENU_H
#define MAINMENU_H

#include "Menu.h"

class MainMenu : public Menu
{
private:
	void createButtons();

public:
	MainMenu();

	void displayMenu(SDL_Event& event, bool& quitGame);
};

#endif // !MAINMENU_H