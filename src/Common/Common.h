#ifndef COMMON_H
#define COMMON_H

#include "../Resource/ResourceManager/ResourceManager.h"
#include "../Entity/Entity.h"
#include "../PickUp/PickUp.h"
#include "../Menu/MainMenu/MainMenu.h"
#include "../Menu/CustomiseMenu/CustomiseMenu.h"
#include "../Menu/OptionsMenu/OptionsMenu.h"
#include "../Entity/Player/Player.h"
#include "../Wave/Wave.h"
#include <memory>

// Screen Dimensions
inline int SCREEN_WIDTH{ 640 };
inline int SCREEN_HEIGHT{ 480 };

// Scale Factor
inline Pair<double> sf{1.0, 1.0};

// Speeds
const int PLAYER_SPEED{ 500 };
const int ENEMY_SPEED{ 250 };
const int PROJECTILE_SPEED{ 600 };

// Manages the game's resources and assets
inline ResourceManager resourceManager{};

// Manages all living entities
inline std::vector<std::unique_ptr<Entity>> gEnts{};
inline std::unique_ptr<Player> gPlayer;
inline Wave gWave{};

inline std::vector<PickUp> gPickUp{};

inline int NUM_OF_PLAYERS{};

inline std::shared_ptr<Menu> activeMenu{};
inline std::shared_ptr<MainMenu> mainMenu = std::make_shared<MainMenu>();
inline std::shared_ptr<CustomiseMenu> customiseMenu = std::make_shared<CustomiseMenu>();
inline std::shared_ptr<OptionsMenu> optionsMenu = std::make_shared<OptionsMenu>();

inline SDL_FRect gRedProjectileClip{ 18, 13, 58, 41 };
inline SDL_FRect gLeftProjectileHitBox{ 26, 7, 4, 27 };
inline SDL_FRect gRightProjectileHitBox{ 28, 7, 4, 27 };

#endif // !COMMON_H
