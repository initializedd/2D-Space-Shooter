#include "Button.h"
#include "Globals.h"
#include "Window.h"
#include <SDL_render.h>

Button::Button()
	: m_rect{}
	, m_text{}
	, m_font{}
	, m_texture{}
	, m_type{}
	, m_selected{}
	, m_down{}
	, m_hover{}
{
}

Button::~Button()
{

}

void Button::createButton(MainMenuButtons type, TTF_Font* font, SDL_Color color)
{
	switch (type)
	{
		case PLAY:
			m_type = PLAY;
			m_text = "Play";
			setRect(200, 100, 200, 50);
			break;

		case CUSTOMISE:
			m_type = CUSTOMISE;
			m_text = "Customise";
			setRect(200, 175, 200, 50);
			break;

		case OPTIONS:
			m_type = OPTIONS;
			m_text = "Options";
			setRect(200, 250, 200, 50);
			break;

		default:
			m_type = TOTAL_BUTTONS;
			break;
	}

	m_texture.loadFromRenderedText(m_text.c_str(), font, color);
}

void Button::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		m_hover = true;

		if (x < m_rect.x || x > m_rect.x + m_rect.w)
			m_hover = false;

		else if (y < m_rect.y || y > m_rect.y + m_rect.h)
			m_hover = false;

		if (m_hover)
		{
			switch (event.type)
			{
				case SDL_MOUSEMOTION:
					printf("Mouse hovering...\n");
					break;

				case SDL_MOUSEBUTTONDOWN:
					printf("Mouse button down...\n");
					m_down = true;
					break;

				case SDL_MOUSEBUTTONUP:
					printf("Mouse button up...\n");
					m_selected = true;
					break;
			}
		}
		else
		{
			m_down = false;
			m_selected = false;
		}
	}
}

void Button::renderButton()
{
	if (m_hover)
	{
		SDL_SetRenderDrawColor(gWindow.getRenderer(), 0xFF, 0xFF, 0xFF, 0x22);
		SDL_RenderFillRect(gWindow.getRenderer(), &m_rect);
	}

	SDL_SetRenderDrawColor(gWindow.getRenderer(), m_hover ? 0x00 : 0xFF, 0xFF, m_hover ? 0x00 : 0xFF, 0xFF);
	SDL_RenderDrawRect(gWindow.getRenderer(), &m_rect);

	int x = m_rect.x + (m_rect.w / 2) - (m_texture.getWidth() / 2);
	int y = m_rect.y + (m_rect.h / 2) - (m_texture.getHeight() / 2);

	if (m_down) 
	{
		y += 2;
	}

	m_texture.render(x, y);
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