#ifndef GLOBALS_H
#define GLOBALS_H

#include "Window.h"
#include "Player.h"
#include "Wave.h"
#include "Texture.h"
#include "Sound.h"
#include "Constants.h"
#include <SDL_ttf.h>
#include <array>

inline Texture					gShipsSprite{};

SDL_Rect head1{ 52, 0, 24, 33 };
SDL_Rect body1{ 0, 52, 128, 89 };
SDL_Rect weapon1{ 25, 32, 78, 21 };
SDL_Rect tail1{ 57, 140, 14, 20 };
std::array ship1{ head1, body1, weapon1, tail1 };

SDL_Rect head2{ 52, 0, 24, 33 };
SDL_Rect body2{ 0, 52, 128, 89 };
SDL_Rect weapon2{ 25, 32, 78, 21 };
SDL_Rect tail2{ 57, 140, 14, 20 };
std::array ship2{ head2, body2, weapon2, tail2 };

SDL_Rect head3{ 35, 0, 58, 146 };
SDL_Rect leftWing3{ 0, 28, 35, 132 };
SDL_Rect rightWing3{ 93, 28, 35, 132 };
std::array ship3{ head3, leftWing3, rightWing3 };

SDL_Rect head4{ 35, 0, 58, 146 };
SDL_Rect leftWing4{ 0, 28, 35, 132 };
SDL_Rect rightWing4{ 93, 28, 35, 132 };
std::array ship4{ head4, leftWing4, rightWing4 };

SDL_Rect head5{ 39, 35, 50, 125 };
SDL_Rect leftWing5{ 0, 26, 40, 124 };
SDL_Rect rightWing5{ 88, 26, 40, 124 };
SDL_Rect topLeftWing5{ 28, 0, 14, 26 };
SDL_Rect topRightWing5{ 86, 0, 14, 26 };
std::array ship5{ head5, leftWing5, rightWing5, topLeftWing5, topRightWing5 };

SDL_Rect head6{ 39, 35, 50, 125 };
SDL_Rect leftWing6{ 0, 26, 40, 124 };
SDL_Rect rightWing6{ 88, 26, 40, 124 };
SDL_Rect topLeftWing6{ 28, 0, 14, 26 };
SDL_Rect topRightWing6{ 86, 0, 14, 26 };
std::array ship6{ head6, leftWing6, rightWing6, topLeftWing6, topRightWing6 };

SDL_Rect head7{ 38, 0, 52, 160 };
SDL_Rect leftWing7{ 0, 49, 38, 83 };
SDL_Rect rightWing7{ 90, 49, 38, 83 };
std::array ship7{ head7, leftWing7, rightWing7 };

SDL_Rect head8{ 38, 0, 52, 160 };
SDL_Rect leftWing8{ 0, 49, 38, 83 };
SDL_Rect rightWing8{ 90, 49, 38, 83 };
std::array ship8{ head8, leftWing8, rightWing8 };

SDL_Rect head9{ 32, 0, 64, 160 };
SDL_Rect leftWing9{ 0, 16, 32, 144 };
SDL_Rect rightWing9{ 96, 16, 32, 144 };
std::array ship9{ head9, leftWing9, rightWing9 };

SDL_Rect head10{ 32, 0, 64, 160 };
SDL_Rect leftWing10{ 0, 16, 32, 144 };
SDL_Rect rightWing10{ 96, 16, 32, 144 };
std::array ship10{ head10, leftWing10, rightWing10 };

SDL_Rect head11{ 42, 0, 44, 147 };
SDL_Rect leftWing11{ 0, 56, 42, 104 };
SDL_Rect rightWing11{ 86, 56, 42, 104 };
std::array ship11{ head11, leftWing11, rightWing11 };

SDL_Rect head12{ 42, 0, 44, 147 };
SDL_Rect leftWing12{ 0, 56, 42, 104 };
SDL_Rect rightWing12{ 86, 56, 42, 104 };
std::array ship12{ head12, leftWing12, rightWing12 };

SDL_Rect head13{ 27, 27, 57, 130 };
SDL_Rect leftWing13{ 0, 0, 27, 160 };
SDL_Rect rightBody13{ 84, 3, 23, 139 };
SDL_Rect rightWing13{ 107, 54, 21, 62 };
std::array ship13{ head13, leftWing13, rightBody13, rightWing13 };

SDL_Rect head14{ 27, 27, 57, 130 };
SDL_Rect leftWing14{ 0, 0, 27, 160 };
SDL_Rect rightBody14{ 84, 3, 23, 139 };
SDL_Rect rightWing14{ 107, 54, 21, 62 };
std::array ship14{ head14, leftWing14, rightBody14, rightWing14 };

SDL_Rect head15{ 34, 36, 60, 123 };
SDL_Rect leftWing15{ 0, 0, 34, 157 };
SDL_Rect rightBody15{ 94, 0, 34, 157 };
std::array ship15{ head15, leftWing15, rightBody15 };

SDL_Rect head16{ 34, 36, 60, 123 };
SDL_Rect leftWing16{ 0, 0, 34, 157 };
SDL_Rect rightBody16{ 94, 0, 34, 157 };
std::array ship16{ head16, leftWing16, rightBody16 };

SDL_Rect head17{ 20, 0, 88, 160 };
SDL_Rect leftWing17{ 0, 20, 20, 86 };
SDL_Rect rightWing17{ 108, 20, 20, 86 };
std::array ship17{ head17, leftWing17, rightWing17 };

SDL_Rect head18{ 20, 0, 88, 160 };
SDL_Rect leftWing18{ 0, 20, 20, 86 };
SDL_Rect rightWing18{ 108, 20, 20, 86 };
std::array ship18{ head18, leftWing18, rightWing18 };

SDL_Rect head19{ 36, 25, 56, 122 };
SDL_Rect leftWing19{ 0, 0, 36, 160 };
SDL_Rect rightWing19{ 92, 0, 36, 160 };
std::array ship19{ head19, leftWing19, rightWing19 };

SDL_Rect head20{ 36, 25, 56, 122 };
SDL_Rect leftWing20{ 0, 0, 36, 160 };
SDL_Rect rightWing20{ 92, 0, 36, 160 };
std::array ship20{ head20, leftWing20, rightWing20 };

SDL_Rect head21{ 32, 0, 64, 157 };
SDL_Rect leftWing21{ 0, 11, 32, 149 };
SDL_Rect rightWing21{ 96, 11, 32, 149 };
std::array ship21{ head21, leftWing21, rightWing21 };

SDL_Rect head22{ 32, 0, 64, 157 };
SDL_Rect leftWing22{ 0, 11, 32, 149 };
SDL_Rect rightWing22{ 96, 11, 32, 149 };
std::array ship22{ head22, leftWing22, rightWing22 };

SDL_Rect head23{ 40, 0, 48, 113 };
SDL_Rect leftWing23{ 0, 25, 40, 133 };
SDL_Rect rightWing23{ 88, 25, 40, 133 };
std::array ship23{ head23, leftWing23, rightWing23 };

SDL_Rect head24{ 40, 0, 48, 113 };
SDL_Rect leftWing24{ 0, 25, 40, 133 };
SDL_Rect rightWing24{ 88, 25, 40, 133 };
std::array ship24{ head24, leftWing24, rightWing24 };

SDL_Rect head25{ 35, 0, 58, 113 };
SDL_Rect leftWing25{ 0, 40, 35, 118 };
SDL_Rect rightWing25{ 93, 40, 35, 118 };
std::array ship25{ head25, leftWing25, rightWing25 };

SDL_Rect head26{ 34, 0, 60, 133 };
SDL_Rect leftWing26{ 0, 17, 34, 143 };
SDL_Rect rightWing26{ 94, 17, 34, 143 };
std::array ship26{ head26, leftWing26, rightWing26 };

SDL_Rect head27{ 34, 0, 60, 133 };
SDL_Rect leftWing27{ 0, 17, 34, 143 };
SDL_Rect rightWing27{ 94, 17, 34, 143 };
std::array ship27{ head27, leftWing27, rightWing27 };

SDL_Rect head28{ 45, 0, 38, 121 };
SDL_Rect leftWing28{ 1, 11, 44, 148 };
SDL_Rect rightWing28{ 83, 11, 44, 148 };
std::array ship28{ head28, leftWing28, rightWing28 };

SDL_Rect head29{ 45, 0, 38, 121 };
SDL_Rect leftWing29{ 1, 11, 44, 148 };
SDL_Rect rightWing29{ 83, 11, 44, 148 };
std::array ship29{ head29, leftWing29, rightWing29 };

SDL_Rect head30{ 48, 0, 32, 144 };
SDL_Rect leftWeapon30{ 25, 31, 23, 129 };
SDL_Rect rightWeapon30{ 80, 31, 23, 129 };
SDL_Rect leftWing30{ 0, 70, 25, 87 };
SDL_Rect rightWing30{ 103, 70, 25, 87 };
std::array ship30{ head30, leftWeapon30, rightWeapon30, leftWing30, rightWing30 };

SDL_Rect head31{ 29, 0, 70, 160 };
SDL_Rect leftWing31{ 0, 47, 29, 81 };
SDL_Rect rightWing31{ 99, 47, 29, 81 };
std::array ship31{ head31, leftWing31, rightWing31 };

SDL_Rect head32{ 27, 0, 74, 160 };
SDL_Rect leftWing32{ 0, 47, 27, 113 };
SDL_Rect rightWing32{ 101, 47, 27, 113 };
std::array ship32{ head32, leftWing32, rightWing32 };

SDL_Rect head33{ 37, 0, 54, 160 };
SDL_Rect leftWing33{ 0, 44, 37, 57 };
SDL_Rect rightWing33{ 91, 44, 37, 57 };
std::array ship33{ head33, leftWing33, rightWing33 };

SDL_Rect head34{ 37, 0, 54, 160 };
SDL_Rect leftWing34{ 0, 44, 37, 57 };
SDL_Rect rightWing34{ 91, 44, 37, 57 };
std::array ship34{ head34, leftWing34, rightWing34 };

SDL_Rect head35{ 21, 0, 86, 160 };
SDL_Rect leftWing35{ 0, 32, 21, 93 };
SDL_Rect rightWing35{ 107, 32, 21, 93 };
std::array ship35{ head35, leftWing35, rightWing35 };

SDL_Rect head36{ 29, 0, 70, 160 };
SDL_Rect leftWing36{ 0, 22, 29, 83 };
SDL_Rect rightWing36{ 99, 22, 29, 83 };
std::array ship36{ head36, leftWing36, rightWing36 };

SDL_Rect head37{ 30, 0, 68, 160 };
SDL_Rect leftWing37{ 0, 28, 30, 64 };
SDL_Rect rightWing37{ 98, 28, 30, 64 };
std::array ship37{ head37, leftWing37, rightWing37 };

SDL_Rect head38{ 39, 0, 68, 160 };
SDL_Rect leftWing38{ 0, 28, 30, 64 };
SDL_Rect rightWing38{ 98, 28, 30, 64 };
std::array ship38{ head38, leftWing38, rightWing38 };

SDL_Rect head39{ 30, 0, 68, 127 };
SDL_Rect leftWing39{ 0, 67, 30, 93 };
SDL_Rect rightWing39{ 98, 67, 30, 93 };
std::array ship39{ head39, leftWing39, rightWing39 };

SDL_Rect head40{ 44, 0, 40, 160 };
SDL_Rect leftWing40{ 0, 41, 44, 114 };
SDL_Rect rightWing40{ 84, 41, 44, 114 };
std::array ship40{ head40, leftWing40, rightWing40 };

SDL_Rect head41{ 46, 0, 36, 160 };
SDL_Rect leftWing41{ 24, 59, 22, 99 };
SDL_Rect rightWing41{ 82, 59, 22, 99 };
std::array ship41{ head41, leftWing41, rightWing41 };

SDL_Rect head42{ 39, 0, 50, 160 };
SDL_Rect leftWing42{ 16, 39, 23, 108 };
SDL_Rect rightWing42{ 89, 39, 23, 108 };
std::array ship42{ head42, leftWing42, rightWing42 };

SDL_Rect head43{ 41, 0, 48, 160 };
SDL_Rect leftWing43{ 27, 51, 14, 46 };
SDL_Rect rightWing43{ 89, 51, 14, 46 };
std::array ship43{ head43, leftWing43, rightWing43 };

SDL_Rect head44{ 50, 0, 29, 160 };
SDL_Rect leftWing44{ 33, 57, 17, 70 };
SDL_Rect rightWing44{ 79, 57, 17, 70 };
std::array ship44{ head44, leftWing44, rightWing44 };

SDL_Rect head45{ 50, 0, 28, 160 };
SDL_Rect leftWing45{ 35, 66, 15, 31 };
SDL_Rect rightWing45{ 78, 66, 15, 31 };
std::array ship45{ head45, leftWing45, rightWing45 };

SDL_Rect head46{ 43, 0, 42, 160 };
SDL_Rect leftWing46{ 29, 62, 14, 58 };
SDL_Rect rightWing46{ 85, 62, 14, 58 };
std::array ship46{ head46, leftWing46, rightWing46 };

SDL_Rect head47{ 50, 0, 28, 160 };
SDL_Rect leftWing47{ 41, 66, 9, 30 };
SDL_Rect rightWing47{ 78, 66, 9, 30 };
std::array ship47{ head47, leftWing47, rightWing47 };

SDL_Rect head48{ 46, 0, 36, 160 };
SDL_Rect leftWing48{ 24, 52, 22, 80 };
SDL_Rect rightWing48{ 82, 52, 22, 80 };
std::array ship48{ head48, leftWing48, rightWing48 };

inline std::array<SDL_Rect[], 48>							   gShipColliders{ ship1, ship2, ship3, ship4, ship5, ship6, ship7, ship8, ship9, ship10, ship11, ship12, ship13, ship14,
															   ship15, ship16, ship17, ship18, ship19, ship20, ship21, ship22, ship23, ship24, ship25, ship26, ship27,
															   ship28, ship29, ship30, ship31, ship32, ship33, ship34, ship35, ship36, ship37, ship38, ship39, ship40,
															   ship41, ship42, ship43, ship44, ship45, ship46, ship47, ship48 };

// Window
inline Window					gWindow{};
inline SDL_Surface*				gWindowIconTexture{};

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
inline SDL_Rect					gRightProjectileHitBox{ 26, 6, 4, 27 };

// Entities
inline std::vector<Entity*>		gEnts;
inline int						ENTITY_ID{};

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