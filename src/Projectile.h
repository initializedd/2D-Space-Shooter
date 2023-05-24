#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Texture.h"
#include "Pair.h"
#include <vector>

class Entity;
enum EntityType;

enum ProjectileType
{
	LEFT_PROJECTILE,
	RIGHT_PROJECTILE
};

class Projectile
{
private:
	Pair<float>				m_pos;
	Vector2<float>			m_vel;
	Texture					m_texture;
	ProjectileType			m_type;
	SDL_Rect				m_collider;
	int						m_damage;

public:
	Projectile();
	~Projectile();

	void move(double dt);

	bool checkScreenBoundary();
	bool checkCollision(std::vector<Entity*>& ents, EntityType ownerType);
	void updateCollider();

	void calculateVelocity(Vector2<float> direction, int speed);
	void render();
	void drawCollision();
	void debug();

	int getPosX() const;
	int getPosY() const;
	int getVelX() const;
	int getVelY() const;
	Texture& getTexture();
	ProjectileType getType();
	SDL_Rect& getCollider();

	void setPos(Pair<int> pos);
	void setVel(Vector2<float> vel);
	void setTexture(Texture& texture);
	void setType(ProjectileType type);
};

#endif // !PROJECTILE_H