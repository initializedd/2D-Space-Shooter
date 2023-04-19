#ifndef ENEMY_H
#define ENEMY_H

#include "Texture.h"
#include "Particle.h"
#include "Weapon.h"
#include "Pair.h"

class Enemy
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
	Enemy(int x, int y);
	~Enemy();

	void move();
	void shoot();

	void animateExhaust(int flameFrames);

	bool checkCollision(SDL_Rect& box);

	bool isDead();
	void reduceHealth(int damage);

	std::vector<SDL_Rect>& getColliders();
	Texture& getTexture();
	Particle& getParticle();
	int getPosX() const;
	int getPosY() const;
	int getHealth() const;
	int getWidth() const;
	int getHeight() const;

	void setCollider();
};

#endif // !ENEMY_H