#ifndef MENU_H
#define MENU_H

#include "Button.h"
#include <vector>

class Menu
{
private:
	std::vector<Button>			m_buttons;
	bool						m_quit;

public:
	Menu();
	~Menu();

	void displayMenu(SDL_Event& event, bool& quitGame);

	bool isQuit();

	std::vector<Button>& getButtons();
};

#endif // !MENU_H