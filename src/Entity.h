#ifndef ENTITY_H
#define ENTITY_H

#include "Texture.h"
#include "Weapon.h"
#include "Particle.h"
#include "Pair.h"
#include <vector>

class Entity
{
protected:
	Texture					m_texture;
	int						m_width;
	int						m_height;

	Pair<int>				m_pos;
	Pair<int>				m_vel;

	Pair<int>				m_leftProjectilePos;
	Pair<int>				m_rightProjectilePos;

	std::vector<SDL_Rect>	m_colliders;

	int						m_health;

	Particle				m_particle;
	int						m_explosionFrames;

	Weapon					m_weapon;

public:
	Entity();
	~Entity();

	virtual void move();
	virtual void shoot(int delay);

	int deathAnimation();

	void reduceHealth(int damage);
	bool isDead();

	std::vector<SDL_Rect>& getColliders();
	Texture& getTexture();
	Particle& getParticle();
	Weapon& getWeapon();
	int getHealth() const;
	int getPosX() const;
	int getPosY() const;
};

#endif // !ENTITY_H