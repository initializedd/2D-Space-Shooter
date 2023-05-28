#ifndef GLOBALS_H
#define GLOBALS_H

#include "Window.h"
#include "Menu.h"
#include "MainMenu.h"
#include "CustomiseMenu.h"
#include "Player.h"
#include "Wave.h"
#include "Texture.h"
#include "Sound.h"
#include "Constants.h"
#include <SDL_ttf.h>
#include <vector>

inline Texture					gShipsSprite{};

// Window
inline Window					gWindow{};
inline SDL_Surface*				gWindowIconTexture{};

// Menus
inline Menu*					gActiveMenu{};
inline MainMenu*				gMainMenu;
inline CustomiseMenu*			gCustomiseMenu;

// Background Textures
inline Texture					gBackgroundTexture{};

// Text Textures
inline Texture					gFpsTextTexture{};

// Fonts
inline TTF_Font*				gFuturaFont{};

// Particle Effects
inline Particle					gExhaustParticle{};
inline Particle					gExplosionParticle{};

// Sound Effects
inline Sound					gExplosionSound{};

// Projectiles
inline Texture					gProjectileTexture{};
inline Sound					gProjectileSound{};
inline SDL_Rect					gRedProjectileClip{ 18, 13, 58, 41 };
inline SDL_Rect					gLeftProjectileHitBox{ 26, 7, 4, 27 };
inline SDL_Rect					gRightProjectileHitBox{ 28, 7, 4, 27 };

// Entities
inline std::vector<Entity*>		gEnts;

// Player
inline Player*					gPlayer{ new Player(SCREEN_WIDTH / 2, SCREEN_HEIGHT) };
inline int						NUM_OF_PLAYERS{};

// Player Collision
inline SDL_Rect					gHeadCollision{ 56, 23, 38, 55 };
inline SDL_Rect					gLeftWingCollision{ 13, 0, 22, 57 };
inline SDL_Rect					gRightWingCollision{ 115, 0, 22, 57 };
inline SDL_Rect					gBodyCollision{ 0, 58, 149, 38 };
inline SDL_Rect					gLowerCollision{ 27, 96, 96, 19 };
inline SDL_Rect					gExhaustCollision{ 51, 115, 48, 16 };

// Enemy
inline Wave						gWave{};
inline Texture					gEnemyTexture{};

// Enemy Collision
inline SDL_Rect					gEnemyHeadCollision{ 0, 69, 170, 38 };
inline SDL_Rect					gEnemyBodyCollision{ 64, 0, 42, 69 };

#endif // !GLOBALS_H