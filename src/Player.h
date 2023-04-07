#ifndef PLAYER_H
#define PLAYER_H

#include "Texture.h"
#include "Weapon.h"
#include "Pair.h"

class Player
{
private:
	Texture		m_texture;
	int			m_width;
	int			m_height;
	Pair		m_pos;
	Pair		m_vel;
	int			m_health;
	Weapon		m_weapon;

public:
	Player();
	~Player();

	void handleEvent(SDL_Event& event);

	void move();
	void shoot();

	bool setTexture(const char* path, const bool flag, const Uint8 red = 0xFF, const Uint8 green = 0xFF, const Uint8 blue = 0xFF);

	Texture& getTexture();
	Weapon& getWeapon();
	int getPosX() const;
	int getPosY() const;
};

#endif // !PLAYER_H