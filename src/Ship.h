#ifndef SHIP_H
#define SHIP_H

#include "ShipPart.h"
#include "Texture.h"
#include "Weapon.h"
#include "Particle.h"
#include "Pair.h"
#include <memory>

// 33 Total Player ships -- SCK
// 21 Total Player Ships -- SCK2

class Ship
{
private:
	std::vector<ShipPart>				m_parts;
	std::shared_ptr<Texture>			m_texture;
	int									m_index;
	//Weapon							m_weapon;
	Particle							m_exhaustParticle;

public:
	Ship();
	~Ship();

	void createShip(int index);

	std::vector<ShipPart>& getParts();
	Texture& getTexture();
	int getIndex();

	void setTexture(std::shared_ptr<Texture>& texture);
};

#endif // !SHIP_H