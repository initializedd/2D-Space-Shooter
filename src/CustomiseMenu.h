#ifndef CUSTOMISE_MENU_H
#define CUSTOMISE_MENU_H

#include "Menu.h"

class CustomiseMenu : public Menu
{
private:
	void createButtons();

public:
	CustomiseMenu();

	void displayMenu(SDL_Event& event, bool& quitGame);
};

#endif // !CUSTOMISE_MENU_H