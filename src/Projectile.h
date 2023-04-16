#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Texture.h"
#include "Pair.h"

class Projectile
{
private:
	Pair<int>		m_pos;
	Pair<int>		m_vel;
	Texture			m_texture;
	SDL_Rect		m_collider;

public:
	Projectile();
	~Projectile();

	void move();

	bool checkCollision(SDL_Rect& box);

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