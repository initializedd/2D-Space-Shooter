#ifndef BUTTON_H
#define BUTTON_H

#include "../../Resource/Texture/Texture.h"
#include <SDL3/SDL_rect.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_events.h>
#include <string>
#include <memory>

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

	// Options Menu Buttons
	RESOLUTION,
	SOUND
};

class Button
{
private:
	ButtonTypes					m_type;
	SDL_FRect					m_rect;
	bool						m_selected;
	bool						m_down;
	bool						m_hover;

public:
	Button(ButtonTypes type, SDL_FRect rect);

	void handleEvent(SDL_Event& event);
	void renderButton();

	bool isSelected();

	ButtonTypes getType();

	void setSelection(bool flag);
};

#endif // !BUTTON_H
