#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Texture.h"
#include "Movement.h"
#include "Collider.h"
#include "Pair.h"
#include <vector>
#include <memory>

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
	Vector2<float>			m_pos;
	Vector2<float>			m_direction;
	Movement				m_movement;
	Collider				m_collider;
	Texture					m_texture;
	ProjectileType			m_type;
	int						m_damage;

public:
	Projectile();

	void move(double dt);

	bool checkScreenBoundary();
	bool checkCollision(std::vector<std::unique_ptr<Entity>>& ents, EntityType ownerType);

	void createCollider();
	void updateCollider();

	void render();
	void debug();

	Vector2<float> getPos() const;
	Texture& getTexture();
	ProjectileType getType();

	void setPos(Pair<int> pos);
	void setDirection(Vector2<float> direction);
	void setTexture(Texture& texture);
	void setType(ProjectileType type);
};

#endif // !PROJECTILE_H