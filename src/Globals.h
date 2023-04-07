#ifndef GLOBALS_H
#define GLOBALS_H

#include "Window.h"
#include "Player.h"
#include "Texture.h"

inline Window			gWindow{};

inline Player			gPlayer{};

inline Texture			gBackgroundTexture{};
inline SDL_Surface*		gWindowIconTexture{};
inline Texture			gProjectileTexture{};

inline SDL_Rect			gRedLaserClip{ 18, 13, 58, 41 };

#endif // !GLOBALS_H