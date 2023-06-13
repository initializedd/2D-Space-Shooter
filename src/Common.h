#ifndef COMMON_H
#define COMMON_H

#include "ResourceManager.h"
#include "Entity.h"
#include "PickUp.h"
#include "MainMenu.h"
#include "CustomiseMenu.h"
#include "Player.h"
#include "Wave.h"
#include <memory>

// Screen Dimensions
const int SCREEN_WIDTH{ 640 };
const int SCREEN_HEIGHT{ 480 };

// Speeds
const int PLAYER_SPEED{ 500 };
const int ENEMY_SPEED{ 250 };
const int PROJECTILE_SPEED{ 600 };

// Manages the game's resources and assets
inline ResourceManager resourceManager{};

// Manages all living entities
inline std::vector<Entity*> gEnts{};
inline std::unique_ptr<Player> gPlayer{};
inline Wave gWave{};

inline std::vector<PickUp> gPickUp{};

inline int NUM_OF_PLAYERS{};

inline Menu* activeMenu{};
inline MainMenu* mainMenu = new MainMenu();
inline CustomiseMenu* customiseMenu = new CustomiseMenu();

inline SDL_Rect					gRedProjectileClip{ 18, 13, 58, 41 };
inline SDL_Rect					gLeftProjectileHitBox{ 26, 7, 4, 27 };
inline SDL_Rect					gRightProjectileHitBox{ 28, 7, 4, 27 };

#endif // !COMMON_H