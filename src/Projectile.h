#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Texture.h"
#include "Pair.h"

class Projectile
{
private:
	Pair		m_pos;
	Pair		m_vel;
	Texture		m_texture;

public:
	Projectile();
	~Projectile();

	void move();

	void setPosX(int x);
	void setPosY(int y);
	void setVelX(int x);
	void setVelY(int y);
	void setTexture(Texture& texture);

	int getPosX() const;
	int getPosY() const;
	int getVelX() const;
	int getVelY() const;
	Texture& getTexture();
};

#endif // !PROJECTILE_H