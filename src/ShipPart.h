#ifndef SHIPPART_H
#define SHIPPART_H

#include "Collider.h"
#include "Pair.h"

enum ShipPartType
{
	COCKPIT,
	LEFT_WEAPON,
	RIGHT_WEAPON,
	WEAPON,
	LEFT_WING,
	RIGHT_WING,
	TOP_LEFT_WING,
	TOP_RIGHT_WING,
	LEFT_CANNON,
	RIGHT_CANNON,
	LEFT_BODY,
	RIGHT_BODY,
	BODY,
	TAIL,
	LEFT_EXHAUST,
	RIGHT_EXHAUST,
	EXHAUST
};

class ShipPart
{
private:
	ShipPartType	m_type;
	Collider		m_collider;
	Pair<int>		m_offset;

public:
	ShipPart(ShipPartType type, SDL_Rect rect);

	Pair<int> getOffset();
	ShipPartType getPart();
};

#endif // !SHIPPART_H