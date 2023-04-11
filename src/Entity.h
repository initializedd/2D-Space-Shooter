#ifndef ENTITY_H
#define ENTITY_H

#include "Texture.h"
#include "Particle.h"
#include "Weapon.h"
#include "Pair.h"

class Entity
{
private:
	Texture						m_texture;
	int							m_width;
	int							m_height;

	Pair<int>					m_pos;
	Pair<int>					m_vel;

	std::vector<SDL_Rect>		m_colliders;

	int							m_health;

	Particle					m_particle;

	Weapon						m_weapon;

public:
	Entity();
	~Entity();

	void move();
	void shoot();

	bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b);
	void shiftColliders();

	std::vector<SDL_Rect>& getColliders();
	Texture& getTexture();
	int getPosX() const;
	int getPosY() const;
};

#endif // !ENTITY_H