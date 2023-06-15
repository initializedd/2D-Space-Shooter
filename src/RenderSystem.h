#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "Window.h"

class RenderSystem
{
private:
	Window		m_window;

public:
	RenderSystem();
	~RenderSystem();

	bool init();

	Window& getWindow();
};

#endif // !RENDER_SYSTEM_H