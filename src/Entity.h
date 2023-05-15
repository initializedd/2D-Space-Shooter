#ifndef ENTITY_H
#define ENTITY_H

#include "Texture.h"
#include "Weapon.h"
#include "Particle.h"
#include "Pair.h"
#include <vector>

enum EntityType
{
	ENTITY,
	PLAYER,
	ENEMY,
	TOTAL_ENTITY
};

class Entity
{
protected:
	EntityType				m_type;
	int						m_id;
	Texture					m_texture;
	int						m_width;
	int						m_height;

	Pair<double>			m_pos;
	Pair<int>				m_vel;

	Pair<int>				m_leftProjectilePos;
	Pair<int>				m_rightProjectilePos;

	std::vector<SDL_Rect>	m_colliders;

	int						m_health;

	Particle				m_particle;
	int						m_explosionFrames;

	Weapon					m_weapon;
	bool					m_canShoot;

public:
	Entity();
	~Entity();

	virtual void move(double dt);
	virtual void shoot(int delay);
	virtual void update(int i, double dt) = 0;
	virtual void handleEvent(SDL_Event& event);

	bool checkCollisionPosX(std::vector<Entity*>& ents);
	bool checkCollisionPosY(std::vector<Entity*>& ents);
	void debug();

	virtual int deathAnimation(double dt);
	virtual void exhaustAnimation(double dt) = 0;

	void reduceHealth(int damage);
	bool isDead();

	std::vector<SDL_Rect>& getColliders();
	Texture& getTexture();
	Particle& getParticle();
	Weapon& getWeapon();
	int getType() const;
	int getHealth() const;
	int getPosX() const;
	int getPosY() const;

	virtual void setColliders() = 0;
};

#endif // !ENTITY_H