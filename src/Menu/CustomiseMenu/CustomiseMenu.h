#ifndef CUSTOMISE_MENU_H
#define CUSTOMISE_MENU_H

#include "../Menu.h"

class CustomiseMenu : public Menu
{
private:
	int m_index;

public:
	CustomiseMenu();

	void createButtons();
	void displayMenu(SDL_Event& event, bool& quitGame);
};

#endif // !CUSTOMISE_MENU_H