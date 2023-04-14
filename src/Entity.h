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

	SDL_Rect					m_collider;

	int							m_health;

	Particle					m_particle;

	Weapon						m_weapon;

public:
	Entity(int x, int y);
	~Entity();

	void move();
	void shoot();

	bool checkCollision(SDL_Rect& box);

	SDL_Rect& getCollider();
	Texture& getTexture();
	int getPosX() const;
	int getPosY() const;

	void setCollider();
};

#endif // !ENTITY_H