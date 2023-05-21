#ifndef MENU_H
#define MENU_H

#include "Texture.h"
#include "Button.h"
#include <vector>

class Menu
{
private:
	Texture						m_backgroundTexture;
	std::vector<Button>			m_buttons;
	bool						m_quit;

public:
	Menu();
	~Menu();

	void displayMenu(SDL_Event& event, bool& quitGame);

	bool isQuit();

	Texture& getTexture();
	std::vector<Button>& getButtons();
};

#endif // !MENU_H