#ifndef GLOBALS_H
#define GLOBALS_H

#include "Window.h"
#include "Player.h"
#include "Texture.h"

inline Window			gWindow{};
inline Texture			gBackgroundTexture{};
inline SDL_Surface*		gWindowIconTexture{};
inline Player			gPlayer{};

#endif // !GLOBALS_H