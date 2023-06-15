#ifndef UI_H
#define UI_H

#include "Widget.h"
#include <vector>

class UI
{
private:
	std::vector<Widget>					m_widgets;

public:
	UI();

	void createUI();

	//void render();

	void displayHealth(int health);
	void displayShield(int shield);

	std::vector<Widget>& getWidgets();
};

#endif // !UI_H