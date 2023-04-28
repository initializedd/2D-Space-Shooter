#include "Button.h"
#include "Globals.h"
#include "Window.h"
#include <SDL_render.h>

Button::Button()
	: m_rect{}
	, m_texture{}
	, m_font{}
	, m_selected{}
	, m_inside{}
{
}

Button::~Button()
{

}

bool Button::createButton(const char* text, TTF_Font* font, SDL_Color color)
{
	if (!m_texture.loadFromRenderedText(text, font, color))
		return false;

	return true;
}

void Button::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		
		m_inside = true;

		if (x < m_rect.x || x > m_rect.x + m_rect.w)
			m_inside = false;

		else if (y < m_rect.y || y > m_rect.y + m_rect.h)
			m_inside = false;

		if (m_inside)
		{
			switch(event.type)
			{
				case SDL_MOUSEMOTION:
					printf("Mouse hovering...\n");
					break;

				case SDL_MOUSEBUTTONDOWN:
					printf("Mouse button down...\n");
					break;

				case SDL_MOUSEBUTTONUP:
					printf("Mouse button up...\n");
					m_selected = true;
					break;
			}
		}
	}
}

void Button::renderButton()
{
	SDL_SetRenderDrawColor(gWindow.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawRect(gWindow.getRenderer(), &m_rect);

	m_texture.render(m_rect.x + (m_rect.w / 2) - m_texture.getWidth() / 2, m_rect.y + (m_rect.h / 2) - (m_texture.getHeight() / 2));
}

void Button::setRect(int x, int y, int w, int h)
{
	m_rect.x = x;
	m_rect.y = y;
	m_rect.w = w;
	m_rect.h = h;
}

bool Button::isSelected()
{
	return m_selected;
}