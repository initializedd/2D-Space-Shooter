#ifndef GLOBALS_H
#define GLOBALS_H

#include "Window.h"
#include "Player.h"
#include "Enemy.h"
#include "Texture.h"
#include "Sound.h"
#include "Constants.h"
#include <SDL_ttf.h>

inline Window			gWindow{};

inline Player			gPlayer{};
inline Enemy			gEnemy{280, 0};

inline Texture			gBackgroundTexture{};
inline SDL_Surface*		gWindowIconTexture{};
inline Texture			gProjectileTexture{};

inline SDL_Rect			gRedLaserClip{ 18, 13, 58, 41 };
inline SDL_Rect			gLeftLaserHitBox{ 26, 10, 4, 22 };
inline SDL_Rect			gRightLaserHitBox{28, 9, 4, 22};
inline Sound			gLaserSound{};

// Enemy Collision
inline SDL_Rect			gEnemyHeadCollision{ 0, 69, 170, 38 };
inline SDL_Rect			gEnemyBodyCollision{ 64, 0, 42, 69 };

// Player Collision
inline SDL_Rect			gHeadCollision{ 56, 23, 38, 55 };
inline SDL_Rect			gLeftWingCollision{ 13, 0, 22, 57 };
inline SDL_Rect			gRightWingCollision{ 115, 0, 22, 57 };
inline SDL_Rect			gBodyCollision{ 0, 58, 149, 38 };
inline SDL_Rect			gLowerCollision{ 27, 96, 96, 19 };
inline SDL_Rect			gExhaustCollision{ 51, 115, 48, 16 };

inline Texture			gFpsTextTexture{};
inline TTF_Font*		gFuturaFont{};

#endif // !GLOBALS_H