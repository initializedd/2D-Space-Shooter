#include "ShipPart.h"

ShipPart::ShipPart(ShipPartType type, SDL_FRect rect)
	: m_type{type}
	, m_collider{rect}
	, m_offset{}
{
}

ShipPartType ShipPart::getPartType()
{
	return m_type;
}

Collider& ShipPart::getCollider()
{
	return m_collider;
}

Pair<int> ShipPart::getOffset()
{
	return m_offset;
}

void ShipPart::setOffset(Pair<int> offset)
{
	m_offset.x = offset.x;
	m_offset.y = offset.y;
}
