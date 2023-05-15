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
	Pair<double>			m_pos;
	Pair<int>				m_vel;
	Texture					m_texture;
	ProjectileType			m_type;
	SDL_Rect				m_collider;
	int						m_damage;

public:
	Projectile();
	~Projectile();

	void move(int vel, double dt);

	bool checkScreenBoundary(SDL_Rect&& screen);
	bool checkCollision(std::vector<Entity*>& ents, EntityType ownerType);
	void updateCollider();

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
	void setVel(Pair<int> vel);
	void setTexture(Texture& texture);
	void setType(ProjectileType type);
	void setCollider(SDL_Rect box);
};

#endif // !PROJECTILE_H