#ifndef FONT_H
#define FONT_H

#include <SDL_ttf.h>
#include <string>

class Font
{
private:
	TTF_Font*		m_font;
	int				m_ptsize;

public:
	Font();
	~Font();

	bool loadFont(const std::string& path, int ptsize);

	TTF_Font* getFont();
};

#endif // !FONT_H