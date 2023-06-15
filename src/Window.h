#ifndef WINDOW_H
#define WINDOW_H

#include "Timer.h"
#include <SDL_video.h>
#include <SDL_render.h>
#include <sstream>

class Window
{
private:
	SDL_Window*					m_window;
	SDL_Surface*				m_icon;
	int							m_width;
	int							m_height;

	SDL_Renderer*				m_renderer;

	std::stringstream			m_fpsText;

public:
	Window();
	~Window();

	bool createWindow();
	bool createRenderer();

	void calculateFPS(Timer& timer, int countedFrames);

	SDL_Window*			getWindow()		const;
	SDL_Renderer*		getRenderer()	const;
	std::stringstream&	getFPS();
};

#endif // !WINDOW_H