#ifndef BUTTON_H
#define BUTTON_H

#include "Texture.h"
#include <SDL_rect.h>
#include <SDL_ttf.h>
#include <SDL_events.h>

class Button
{
private:
	SDL_Rect				m_rect;
	Texture					m_texture;
	TTF_Font*				m_font;
	bool					m_selected;
	bool					m_inside;

public:
	Button();
	~Button();

	bool createButton(const char* text, TTF_Font* font, SDL_Color color);
	void handleEvent(SDL_Event& event);
	void renderButton();

	void setRect(int x, int y, int w, int h);

	bool isSelected();
};

#endif // !BUTTON_H