#ifndef TEXT_H
#define TEXT_H

#include "Texture.h"
#include <SDL_ttf.h>
#include <string>
#include <sstream>
#include <memory>

class Text
{
private:
	Texture						m_texture;

public:
	Text();

	bool loadFromText(const std::string& text, TTF_Font* font, const SDL_Color& color);

	Texture* getTexture();
};

#endif // !TEXT_H