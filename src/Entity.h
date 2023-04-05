#ifndef ENTITY_H
#define ENTITY_H

#include "Texture.h"
#include "Weapon.h"

class Entity
{
private:
	Texture		m_texture;
	int			m_width;
	int			m_height;
	int			m_posX;
	int			m_posY;
	int			m_velX;
	int			m_velY;
	int			m_health;
	Weapon		m_weapon;

public:
	Entity();
	~Entity();

	void handleEvent(SDL_Event& event);

	void move();

	bool setTexture(const char* path, const bool flag, const Uint8 red = 0xFF, const Uint8 green = 0xFF, const Uint8 blue = 0xFF);

	Texture& getTexture();

	int getPosX();
	int getPosY();
};

#endif // !ENTITY_H