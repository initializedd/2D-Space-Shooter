#include "Window.h"
#include "Constants.h"
#include <cstdio>

Window::Window()
	: m_window{}
	, m_renderer{}
	, m_width{}
	, m_height{}
	, m_fpsText{}
{
}

Window::~Window()
{
	if (m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}

	if (m_window)
	{
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}
}

bool Window::createWindow()
{
	m_width = SCREEN_WIDTH;
	m_height = SCREEN_HEIGHT;

	m_window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_SHOWN);
	if (!m_window)
	{
		printf("Failed to create window, Error: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

bool Window::createRenderer()
{
	if (m_window)
	{
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!m_renderer)
		{
			printf("Failed to create renderer, Error: %s\n", SDL_GetError());
			return false;
		}

		SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}

	return true;
}

void Window::free()
{
	if (m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}

	if (m_window)
	{
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}
}

void Window::calculateFPS(Timer& timer, int countedFrames)
{
	float avgFPS = countedFrames / (timer.getTicks() / 1000.f);

	if (avgFPS > 2000000)
		avgFPS = 0.f;

	m_fpsText.str("FPS: " + std::to_string((int)(round(avgFPS))));
}

SDL_Window* Window::getWindow() const
{
	return m_window;
}

SDL_Renderer* Window::getRenderer() const
{
	return m_renderer;
}

std::stringstream& Window::getFPS()
{
	return m_fpsText;
}