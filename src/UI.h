#ifndef UI_H
#define UI_H

#include "Widget.h"
#include <vector>
#include <memory>

class UI
{
private:
	std::vector<Widget>					m_widgets;
	std::shared_ptr<Texture>			m_texture;

public:
	UI();

	void createUI();

	void render();

	Texture& getTexture();
};

#endif // !UI_H