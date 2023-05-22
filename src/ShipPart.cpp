#include "ShipPart.h"

ShipPart::ShipPart(ShipPartType type, SDL_Rect rect)
	: m_type{type}
	, m_collider{rect}
	, m_offset{}
{
}

Pair<int> ShipPart::getOffset()
{
	return m_offset;
}

ShipPartType ShipPart::getPart()
{
	return m_type;
}