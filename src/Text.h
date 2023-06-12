#ifndef FONT_H
#define FONT_H

#include "Texture.h"
#include <SDL_ttf.h>
#include <string>
#include <sstream>
#include <memory>

class Text
{
private:
	TTF_Font*					m_font;
	Texture						m_texture;
	std::stringstream			m_textStream;

public:
	Text();
	~Text();

	bool loadFont(const std::string& path);
	bool loadTextTexture(const std::string& text);
	bool loadFromTextStream(const std::stringstream& text);

	TTF_Font* getFont() const;
	Texture* getTexture();
};

#endif // !FONT_H