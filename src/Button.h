#ifndef BUTTON_H
#define BUTTON_H

#include "Texture.h"
#include <SDL_rect.h>
#include <SDL_ttf.h>
#include <SDL_events.h>
#include <string>

enum ButtonTypes
{
	// Main Menu Buttons
	PLAY,
	CUSTOMISE,
	OPTIONS,

	// Customise Menu Buttons
	BACK,
	LEFT,
	RIGHT,
	SELECT,
};

class Button
{
private:
	ButtonTypes				m_type;
	std::string				m_text;
	TTF_Font*				m_font;
	SDL_Color				m_color;
	SDL_Rect				m_rect;
	Texture					m_texture;
	bool					m_selected;
	bool					m_down;
	bool					m_hover;

public:
	Button(ButtonTypes type, const std::string& text, TTF_Font* font, SDL_Color color, SDL_Rect rect);

	void handleEvent(SDL_Event& event);
	void renderButton();

	bool isSelected();

	ButtonTypes getType();

	void setSelection(bool flag);
};

#endif // !BUTTON_H