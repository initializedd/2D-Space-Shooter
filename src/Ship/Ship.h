#ifndef SHIP_H
#define SHIP_H

#include "ShipPart/ShipPart.h"
#include "../Resource/Texture/Texture.h"
#include "../Weapon/Weapon.h"
#include "../Resource/Sprite/Sprite.h"
#include "../Common/Pair.h"
#include <memory>

// 33 Total Player ships -- SCK
// 21 Total Player Ships -- SCK2

class Ship
{
private:
	std::vector<ShipPart>				m_parts;
	int									m_index;
	//Weapon							m_weapon;
	Sprite								m_exhaustSprite;

public:
	Ship();
	~Ship();

	void createShip(int index);

	std::vector<ShipPart>& getParts();
	int getIndex();
};

#endif // !SHIP_H