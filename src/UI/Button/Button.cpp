#include "Button.h"
#include "../../Game/Game.h"
#include "../../Common/Common.h"
#include <SDL3/SDL_render.h>

Button::Button(ButtonTypes type, SDL_FRect rect)
	: m_type{ type }
	, m_rect{ rect }
	, m_selected{}
	, m_down{}
	, m_hover{}
{
}

void Button::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_EVENT_MOUSE_MOTION || event.type == SDL_EVENT_MOUSE_BUTTON_DOWN || event.type == SDL_EVENT_MOUSE_BUTTON_UP)
	{
		float x, y;
		SDL_GetMouseState(&x, &y);

		m_hover = true;

		SDL_FRect button;
		button.x = m_rect.x * sf.x;
		button.y = m_rect.y * sf.y;
		button.w = m_rect.w * sf.x;
		button.h = m_rect.h * sf.y;

		if (x < button.x || x > button.x + button.w)
			m_hover = false;

		else if (y < button.y || y > button.y + button.h)
			m_hover = false;

		if (m_hover)
		{
			switch (event.type)
			{
				case SDL_EVENT_MOUSE_MOTION:
					break;

				case SDL_EVENT_MOUSE_BUTTON_DOWN:
					m_down = true;
					break;

				case SDL_EVENT_MOUSE_BUTTON_UP:
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
	SDL_FRect button;
	button.x = m_rect.x * sf.x;
	button.y = m_rect.y * sf.y;
	button.w = m_rect.w * sf.x;
	button.h = m_rect.h * sf.y;

	if (m_hover)
	{
		SDL_SetRenderDrawColor(resourceManager.getRenderSystem().getWindow().getRenderer(), 0xFF, 0xFF, 0xFF, 0x22);
		SDL_RenderFillRect(resourceManager.getRenderSystem().getWindow().getRenderer(), &button);
	}

	SDL_SetRenderDrawColor
	(
		resourceManager.getRenderSystem().getWindow().getRenderer(),
		m_hover ? 0x00 : 0xFF,
		0xFF,
		m_hover ? 0x00 : 0xFF,
		0xFF
	);

	SDL_RenderRect(resourceManager.getRenderSystem().getWindow().getRenderer(), &button);

	//int x = m_rect.x + (m_rect.w / 2) - (m_texture->getWidth() / 2);
	int x = button.x + (button.w / 2) - (20 / 2);
	//int y = m_rect.y + (m_rect.h / 2) - (m_texture->getHeight() / 2);
	int y = button.y + (button.h / 2) - (20 / 2);

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
			SDL_FRect rect{ (button.x + (button.w / 2) - (texture->getTexture()->getWidth() / 2)),
						 (button.y + (button.h / 2) - (texture->getTexture()->getHeight() / 2)),
						 (static_cast<float>(texture->getTexture()->getWidth())),
						 (static_cast<float>(texture->getTexture()->getHeight())) };
			texture->getTexture()->render(rect.x, rect.y, rect.w, rect.h, nullptr);
			break;
		}
		case CUSTOMISE:
		{
			std::shared_ptr<Text> texture = resourceManager.getTextSystem().findText("txt_customise");
			SDL_FRect rect{ (button.x + (button.w / 2) - (texture->getTexture()->getWidth() / 2)),
						 (button.y + (button.h / 2) - (texture->getTexture()->getHeight() / 2)),
						 (static_cast<float>(texture->getTexture()->getWidth())),
						 (static_cast<float>(texture->getTexture()->getHeight())) };
			texture->getTexture()->render(rect.x, rect.y, rect.w, rect.h, nullptr);
			break;
		}
		case OPTIONS:
		{
			std::shared_ptr<Text> texture = resourceManager.getTextSystem().findText("txt_options");
			SDL_FRect rect{ (button.x + (button.w / 2) - (texture->getTexture()->getWidth() / 2)),
						 (button.y + (button.h / 2) - (texture->getTexture()->getHeight() / 2)),
						 (static_cast<float>(texture->getTexture()->getWidth())),
						 (static_cast<float>(texture->getTexture()->getHeight())) };
			texture->getTexture()->render(rect.x, rect.y, rect.w, rect.h, nullptr);
			break;
		}

		// Customise Menu Buttons

		case BACK:
		{
			std::shared_ptr<Text> texture = resourceManager.getTextSystem().findText("txt_back");
			SDL_FRect rect{ (button.x + (button.w / 2) - (texture->getTexture()->getWidth() / 2)),
						 (button.y + (button.h / 2) - (texture->getTexture()->getHeight() / 2)),
						 (static_cast<float>(texture->getTexture()->getWidth())),
				         (static_cast<float>(texture->getTexture()->getHeight())) };
			texture->getTexture()->render(rect.x, rect.y, rect.w, rect.h, nullptr);
			break;
		}
		case LEFT:
		{
			std::shared_ptr<Text> texture = resourceManager.getTextSystem().findText("txt_left");
			SDL_FRect rect{ (button.x + (button.w / 2) - (texture->getTexture()->getWidth() / 2)),
						 (button.y + (button.h / 2) - (texture->getTexture()->getHeight() / 2)),
						 (static_cast<float>(texture->getTexture()->getWidth())),
						 (static_cast<float>(texture->getTexture()->getHeight())) };
			texture->getTexture()->render(rect.x, rect.y, rect.w, rect.h, nullptr);
			break;
		}
		case RIGHT:
		{
			std::shared_ptr<Text> texture = resourceManager.getTextSystem().findText("txt_right");
			SDL_FRect rect{ (button.x + (button.w / 2) - (texture->getTexture()->getWidth() / 2)),
						 (button.y + (button.h / 2) - (texture->getTexture()->getHeight() / 2)),
						 (static_cast<float>(texture->getTexture()->getWidth())),
						 (static_cast<float>(texture->getTexture()->getHeight())) };
			texture->getTexture()->render(rect.x, rect.y, rect.w, rect.h, nullptr);
			break;
		}
		case SELECT:
		{
			std::shared_ptr<Text> texture = resourceManager.getTextSystem().findText("txt_select");
			SDL_FRect rect{ (button.x + (button.w / 2) - (texture->getTexture()->getWidth() / 2)),
						 (button.y + (button.h / 2) - (texture->getTexture()->getHeight() / 2)),
						 (static_cast<float>(texture->getTexture()->getWidth())),
						 (static_cast<float>(texture->getTexture()->getHeight())) };
			texture->getTexture()->render(rect.x, rect.y, rect.w, rect.h, nullptr);
			break;
		}

		// Options Menu Buttons

		case RESOLUTION:
		{
			Text resolution{};
			const std::string res = std::to_string(SCREEN_WIDTH) + 'x' + std::to_string(SCREEN_HEIGHT);
			resolution.loadFromText(res, resourceManager.getTextSystem().findFont("ttf_futura")->getFont(), SDL_Color(0xFF, 0xFF, 0xFF, 0xFF));
			SDL_FRect rect{ (button.x + (button.w / 2) - (resolution.getTexture()->getWidth() / 2)),
						 (button.y + (button.h / 2) - (resolution.getTexture()->getHeight() / 2)),
						 (static_cast<float>(resolution.getTexture()->getWidth())),
						 (static_cast<float>(resolution.getTexture()->getHeight())) };
			resolution.getTexture()->render(rect.x, rect.y, rect.w, rect.h, nullptr);
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
