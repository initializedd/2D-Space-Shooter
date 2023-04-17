#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Texture.h"
#include "Pair.h"
#include <vector>

class Enemy;

class Projectile
{
private:
	Pair<int>		m_pos;
	Pair<int>		m_vel;
	Texture			m_texture;
	SDL_Rect		m_collider;
	int				m_damage;

public:
	Projectile();
	~Projectile();

	void move();

	bool checkCollision(std::vector<Enemy>& enemies);
	void drawCollision();

	int getPosX() const;
	int getPosY() const;
	int getVelX() const;
	int getVelY() const;
	Texture& getTexture();
	SDL_Rect& getCollider();

	void setPosX(int x);
	void setPosY(int y);
	void setVelX(int x);
	void setVelY(int y);
	void setTexture(Texture& texture);
	void setCollider(SDL_Rect& box);
};

#endif // !PROJECTILE_H