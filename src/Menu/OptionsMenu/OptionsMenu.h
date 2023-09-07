#ifndef OPTIONS_MENU_H
#define OPTIONS_MENU_H

#include "../Menu.h"

class OptionsMenu : public Menu
{
private:

public:
	OptionsMenu();

	void createButtons();
	void displayMenu(SDL_Event& event, bool& quitGame);
};

#endif // !OPTIONS_MENU_H