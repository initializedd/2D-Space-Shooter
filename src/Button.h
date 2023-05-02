#ifndef BUTTON_H
#define BUTTON_H

#include "Texture.h"
#include <SDL_rect.h>
#include <SDL_ttf.h>
#include <SDL_events.h>
#include <string>

enum MainMenuButtons
{
	PLAY,
	CUSTOMISE,
	OPTIONS,
	TOTAL_BUTTONS
};

class Button
{
private:
	SDL_Rect				m_rect;
	std::string				m_text;
	TTF_Font*				m_font;
	Texture					m_texture;
	MainMenuButtons			m_type;
	bool					m_selected;
	bool					m_inside;

public:
	Button();
	~Button();

	void createButton(MainMenuButtons type, TTF_Font* font, SDL_Color color);
	void handleEvent(SDL_Event& event);
	void renderButton();

	void setRect(int x, int y, int w, int h);

	bool isSelected();
};

#endif // !BUTTON_H