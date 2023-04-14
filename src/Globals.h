#ifndef GLOBALS_H
#define GLOBALS_H

#include "Window.h"
#include "Player.h"
#include "Entity.h"
#include "Texture.h"
#include "Sound.h"
#include "Constants.h"
#include <SDL_ttf.h>

inline Window			gWindow{};

inline Player			gPlayer{};
inline Entity			gEnemy{280, 0};

inline Texture			gBackgroundTexture{};
inline SDL_Surface*		gWindowIconTexture{};
inline Texture			gProjectileTexture{};

inline SDL_Rect			gRedLaserClip{ 18, 13, 58, 41 };
inline Sound			gLaserSound{};

inline Texture			gFpsTextTexture{};
inline TTF_Font*		gFuturaFont{};

#endif // !GLOBALS_H