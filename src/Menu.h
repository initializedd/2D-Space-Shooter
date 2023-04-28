#ifndef MENU_H
#define MENU_H

#include "Button.h"

class Menu
{
private:
	Button				m_button;
	bool				m_quit;

public:
	Menu();
	~Menu();

	void displayMenu(SDL_Event& event, bool& quitGame);

	Button& getButton();
	bool isQuit();
};

#endif // !MENU_H