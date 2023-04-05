#ifndef GLOBALS_H
#define GLOBALS_H

#include "Window.h"
#include "Entity.h"
#include "Texture.h"

inline Window			gWindow{};
inline Texture			gBackgroundTexture{};
inline SDL_Surface*		gWindowIconTexture{};
inline Entity			gPlayer{};

#endif // !GLOBALS_H