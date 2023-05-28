#ifndef ENTITY_H
#define ENTITY_H

#include "Ship.h"
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
	Ship					m_ship;
	EntityType				m_type;
	float					m_textureRotation;
	Vector2<float>			m_direction;
	int						m_width;
	int						m_height;

	SDL_Rect*				m_currentExhaustClip;
	SDL_Rect*				m_currentDeathClip;

	Vector2<float>			m_pos;
	Vector2<float>			m_vel;

	Pair<int>				m_leftCannonPos;
	Pair<int>				m_rightCannonPos;

	int						m_health;
	int						m_shield;

	Particle				m_particle;

	int						m_explosionFrames;
	int						m_flameFrames;

	Weapon					m_weapon;
	bool					m_canShoot;

public:
	Entity();

	virtual void move(double dt);
	void shoot(int delay);
	virtual void update(int i, double dt) = 0;
	virtual void render() = 0;
	virtual void handleEvent(SDL_Event& event);

	void calculateVelocity(Vector2<float> direction, int speed);

	virtual void checkScreenBoundaryX();
	virtual void checkScreenBoundaryY();
	bool checkCollisionPosX(std::vector<Entity*>& ents);
	bool checkCollisionPosY(std::vector<Entity*>& ents);
	void debug();

	bool deathAnimation();
	void exhaustAnimation();

	void renderDeathAnimation();

	void reduceHealth(int damage);
	bool isDead();

	Ship& getShip();
	Particle& getParticle();
	Weapon& getWeapon();
	int getType() const;
	int getHealth() const;
	Vector2<float> getPos() const;

	void setColliders();
};

#endif // !ENTITY_H