#ifndef ENTITY_H
#define ENTITY_H

#include "../Ship/Ship.h"
#include "../Physics/Movement/Movement.h"
#include "../Weapon/Weapon.h"
#include "../Resource/Sprite/Sprite.h"
#include "../Timer/Timer.h"
#include "../Common/Pair.h"
#include <vector>

enum EntityType : int
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
	int						m_speed;
	int						m_width;
	int						m_height;

	SDL_FRect*				m_currentExhaustClip;
	SDL_FRect*				m_currentDeathClip;

	Vector2<float>			m_pos;
	Movement				m_movement;

	Pair<int>				m_leftCannonPos;
	Pair<int>				m_rightCannonPos;

	int						m_health;
	int						m_shield;

	Sprite					m_sprite;

	int						m_explosionFrames;
	int						m_flameFrames;

	Weapon					m_weapon;
	bool					m_canShoot;
	Timer													m_lastShot;


public:
	Entity();
	virtual ~Entity();

	virtual void move(double dt);
	virtual void shoot(int delay);
	virtual void update(int i, double dt) = 0;
	virtual void render() = 0;
	virtual void handleKeyboardInputs();

	void checkScreenBoundary();
	void checkCollision(std::vector<std::unique_ptr<Entity>>& ents);
	void debug();

	bool deathAnimation();
	void exhaustAnimation();

	void renderDeathAnimation();

	void reduceHealth(int damage);
	bool isDead();

	Ship& getShip();
	Sprite& getSprite();
	Weapon& getWeapon();
	int getType() const;
	int getHealth() const;
	Vector2<float> getPos() const;

	void createColliders();
};

#endif // !ENTITY_H
