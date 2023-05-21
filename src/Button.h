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
	MAIN_TOTAL_BUTTONS
};

enum CustomiseMenuButtons
{
	BACK,
	LEFT,
	RIGHT,
	SELECT,
	CUSTOMISE_TOTAL_BUTTONS
};


class Button
{
private:
	SDL_Rect				m_rect;
	std::string				m_text;
	TTF_Font*				m_font;
	Texture					m_texture;
	MainMenuButtons			m_mainMenuType;
	CustomiseMenuButtons	m_customiseMenuType;
	bool					m_selected;
	bool					m_down;
	bool					m_hover;

public:
	Button();
	~Button();

	void createButton(MainMenuButtons type, TTF_Font* font, SDL_Color color);
	void createButton(CustomiseMenuButtons type, TTF_Font* font, SDL_Color color);

	void handleEvent(SDL_Event& event);
	void renderButton();

	void setRect(int x, int y, int w, int h);

	bool isSelected();

	MainMenuButtons	getMainType();
	CustomiseMenuButtons getCustomiseType();

	void setSelection(bool flag);
};

#endif // !BUTTON_H