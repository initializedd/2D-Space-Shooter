#include "Button.h"
#include "Game.h"
#include "Common.h"
#include <SDL_render.h>

Button::Button(ButtonTypes type, SDL_Rect rect)
	: m_type{ type }
	, m_rect{ rect }
	, m_selected{}
	, m_down{}
	, m_hover{}
{
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
		SDL_SetRenderDrawColor(resourceManager.getRenderSystem().getWindow().getRenderer(), 0xFF, 0xFF, 0xFF, 0x22);
		SDL_RenderFillRect(resourceManager.getRenderSystem().getWindow().getRenderer(), &m_rect);
	}

	SDL_SetRenderDrawColor
	(
		resourceManager.getRenderSystem().getWindow().getRenderer(),
		m_hover ? 0x00 : 0xFF,
		0xFF,
		m_hover ? 0x00 : 0xFF,
		0xFF
	);

	SDL_RenderDrawRect(resourceManager.getRenderSystem().getWindow().getRenderer(), &m_rect);

	//int x = m_rect.x + (m_rect.w / 2) - (m_texture->getWidth() / 2);
	int x = m_rect.x + (m_rect.w / 2) - (20 / 2);
	//int y = m_rect.y + (m_rect.h / 2) - (m_texture->getHeight() / 2);
	int y = m_rect.y + (m_rect.h / 2) - (20 / 2);

	if (m_down)
	{
		y += 2;
	}

	switch (m_type)
	{
		// Main Menu Buttons

		case PLAY:
		{
			std::shared_ptr<Text> texture = resourceManager.getTextSystem().findText("txt_play");
			SDL_Rect rect{ (m_rect.x + (m_rect.w / 2) - (texture->getTexture()->getWidth() / 2)),
						 (m_rect.y + (m_rect.h / 2) - (texture->getTexture()->getHeight() / 2)),
						 (texture->getTexture()->getWidth()), 
						 (texture->getTexture()->getHeight()) };
			texture->getTexture()->render(rect.x, rect.y, rect.w, rect.h, nullptr);
			break;
		}
		case CUSTOMISE:
		{
			std::shared_ptr<Text> texture = resourceManager.getTextSystem().findText("txt_customise");
			SDL_Rect rect{ (m_rect.x + (m_rect.w / 2) - (texture->getTexture()->getWidth() / 2)),
						 (m_rect.y + (m_rect.h / 2) - (texture->getTexture()->getHeight() / 2)),
						 (texture->getTexture()->getWidth()), 
						 (texture->getTexture()->getHeight()) };
			texture->getTexture()->render(rect.x, rect.y, rect.w, rect.h, nullptr);
			break;
		}
		case OPTIONS:
		{
			std::shared_ptr<Text> texture = resourceManager.getTextSystem().findText("txt_options");
			SDL_Rect rect{ (m_rect.x + (m_rect.w / 2) - (texture->getTexture()->getWidth() / 2)),
						 (m_rect.y + (m_rect.h / 2) - (texture->getTexture()->getHeight() / 2)),
						 (texture->getTexture()->getWidth()), 
						 (texture->getTexture()->getHeight()) };
			texture->getTexture()->render(rect.x, rect.y, rect.w, rect.h, nullptr);
			break;
		}

		// Customise Menu Buttons

		case BACK:
		{
			std::shared_ptr<Text> texture = resourceManager.getTextSystem().findText("txt_back");
			SDL_Rect rect{ (m_rect.x + (m_rect.w / 2) - (texture->getTexture()->getWidth() / 2)),
						 (m_rect.y + (m_rect.h / 2) - (texture->getTexture()->getHeight() / 2)),
						 (texture->getTexture()->getWidth()), 
				         (texture->getTexture()->getHeight()) };
			texture->getTexture()->render(rect.x, rect.y, rect.w, rect.h, nullptr);
			break;
		}
		case LEFT:
		{
			std::shared_ptr<Text> texture = resourceManager.getTextSystem().findText("txt_left");
			SDL_Rect rect{ (m_rect.x + (m_rect.w / 2) - (texture->getTexture()->getWidth() / 2)),
						 (m_rect.y + (m_rect.h / 2) - (texture->getTexture()->getHeight() / 2)),
						 (texture->getTexture()->getWidth()), 
						 (texture->getTexture()->getHeight()) };
			texture->getTexture()->render(rect.x, rect.y, rect.w, rect.h, nullptr);
			break;
		}
		case RIGHT:
		{
			std::shared_ptr<Text> texture = resourceManager.getTextSystem().findText("txt_right");
			SDL_Rect rect{ (m_rect.x + (m_rect.w / 2) - (texture->getTexture()->getWidth() / 2)),
						 (m_rect.y + (m_rect.h / 2) - (texture->getTexture()->getHeight() / 2)),
						 (texture->getTexture()->getWidth()), 
						 (texture->getTexture()->getHeight()) };
			texture->getTexture()->render(rect.x, rect.y, rect.w, rect.h, nullptr);
			break;
		}
		case SELECT:
		{
			std::shared_ptr<Text> texture = resourceManager.getTextSystem().findText("txt_select");
			SDL_Rect rect{ (m_rect.x + (m_rect.w / 2) - (texture->getTexture()->getWidth() / 2)),
						 (m_rect.y + (m_rect.h / 2) - (texture->getTexture()->getHeight() / 2)),
						 (texture->getTexture()->getWidth()), 
						 (texture->getTexture()->getHeight()) };
			texture->getTexture()->render(rect.x, rect.y, rect.w, rect.h, nullptr);
			break;
		}
	}
}

bool Button::isSelected()
{
	if (m_selected)
	{
		m_selected = false; // reset back to default state once handled
		return true;
	}

	return false;
}

ButtonTypes Button::getType()
{
	return m_type;
}

void Button::setSelection(bool flag)
{
	m_selected = flag;
}
