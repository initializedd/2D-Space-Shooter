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

public:
	Projectile();
	~Projectile();

	void move();

	int getPosX() const;
	int getPosY() const;
	int getVelX() const;
	int getVelY() const;
	Texture& getTexture();

	void setPosX(int x);
	void setPosY(int y);
	void setVelX(int x);
	void setVelY(int y);
	void setTexture(Texture& texture);
};

#endif // !PROJECTILE_H