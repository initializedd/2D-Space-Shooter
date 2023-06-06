#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "Window.h"

class RenderSystem
{
private:
	Window m_window;

public:
	RenderSystem();

	bool init();
	void free();
};

#endif // !RENDER_SYSTEM_H