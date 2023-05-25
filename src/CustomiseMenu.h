#ifndef CUSTOMISEMENU_H
#define CUSTOMISEMENU_H

#include "Menu.h"

class CustomiseMenu : public Menu
{
private:
	void createButtons();

public:
	CustomiseMenu();

	void displayMenu(SDL_Event& event, bool& quitGame);
};

#endif // !CUSTOMISEMENU_H