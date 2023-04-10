#ifndef WINDOW_H
#define WINDOW_H

#include <SDL_video.h>
#include <SDL_render.h>

class Window
{
private:
	SDL_Window*		m_window;
	int				m_width;
	int				m_height;

	SDL_Renderer*	m_renderer;

public:
	Window();
	~Window();

	bool createWindow();
	bool createRenderer();

	SDL_Window*		getWindow()		const;
	SDL_Renderer*	getRenderer()	const;
	
	void free();

};

#endif // !WINDOW_H