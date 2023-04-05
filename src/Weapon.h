#ifndef WEAPON_H
#define WEAPON_H

#include "Texture.h"
#include <string>

class Weapon
{
private:
	std::string		m_name;
	int				m_damage;
	Texture			m_texture;

public:
	Weapon();
	~Weapon();

	void shoot();

	const std::string& getName() const;
	const int getDamage() const;
	const Texture& getTexture() const;
};

#endif // !WEAPON_H