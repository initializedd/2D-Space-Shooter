#include "Ship.h"
#include "Common.h"

Ship::Ship()
	: //m_pos{}
	  m_parts{}
	, m_index{}
	//, m_weapon{}
	, m_exhaustSprite{}
{
}

Ship::~Ship()
{
}

void Ship::createShip(int index)
{
	switch(index)
	{
		case 0:
		case 1:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(26 * sf.x, 0 * sf.y, 12 * sf.x, 17 * sf.y)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(21 * sf.x, 16 * sf.y, 2 * sf.x, 10 * sf.y)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(41 * sf.x, 16 * sf.y, 2 * sf.x, 10 * sf.y)),
						ShipPart(WEAPON,			SDL_Rect(11 * sf.x, 16 * sf.y, 42 * sf.x, 11 * sf.y)),
						ShipPart(BODY,				SDL_Rect(0 * sf.x, 26 * sf.y, 64 * sf.x, 45 * sf.y)),
						ShipPart(TAIL,				SDL_Rect(29 * sf.x, 70 * sf.y, 7 * sf.x, 10 * sf.y)) };
			break;

		case 2:
		case 3:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(18, 0, 29, 73)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(18, 25, 6, 8)),		
						ShipPart(RIGHT_WEAPON,		SDL_Rect(46, 25, 6, 8)),		
						ShipPart(LEFT_WING,			SDL_Rect(0, 14, 18, 66)),
						ShipPart(RIGHT_WING,		SDL_Rect(47, 14, 18, 66)) };
			break;

		case 4:
		case 5:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(20, 18, 25, 63)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(18, 27, 2, 7)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(44, 27, 2, 7)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 13, 20, 62)),
						ShipPart(RIGHT_WING,		SDL_Rect(44, 13, 20, 62)), 
						ShipPart(TOP_LEFT_WING,		SDL_Rect(14, 0, 7, 13)),
						ShipPart(TOP_RIGHT_WING,	SDL_Rect(43, 0, 7, 13)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(22, 80, 8, 10)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(34, 80, 8, 10)) };
			break;

		case 6:
		case 7:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(19, 0, 26, 80)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(23, 6, 2, 9)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(39, 6, 2, 9)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 25, 19, 42)),
						ShipPart(RIGHT_WING,		SDL_Rect(45, 25, 19, 42)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(6, 57, 10, 10)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(49, 57, 20, 20)) };
			break;

		case 8:
		case 9:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(16, 0, 32, 80)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(30, 0, 2, 5)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(33, 0, 2, 5)),	
						ShipPart(LEFT_WING,			SDL_Rect(0, 8, 16, 72)),
						ShipPart(RIGHT_WING,		SDL_Rect(48, 8, 16, 72)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(18, 80, 13, 10)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(34, 80, 13, 10)) };
			break;

		case 10:
		case 11:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(21, 0, 22, 79)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(4, 28, 2, 8)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(58, 28, 2, 8)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 28, 21, 52)),
						ShipPart(RIGHT_WING,		SDL_Rect(43, 28, 21, 52)) };
			break;

		case 12:
		case 13:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(14, 14, 29, 65)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(31, 14, 1, 5)),	
						ShipPart(RIGHT_WEAPON,		SDL_Rect(33, 14, 1, 5)),	
						ShipPart(LEFT_WING,			SDL_Rect(0, 0, 14, 80)),
						ShipPart(RIGHT_BODY,		SDL_Rect(42, 2, 12, 70)),
						ShipPart(RIGHT_WING,		SDL_Rect(59, 27, 11, 31)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(24, 79, 14, 10)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(46, 71, 5, 10)) };
			break;

		case 14:
		case 15:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(17, 18, 30, 62)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(24, 18, 2, 14)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(39, 18, 2, 9)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 0, 17, 79)),
						ShipPart(RIGHT_BODY,		SDL_Rect(47, 0, 17, 79)),
						ShipPart(EXHAUST,			SDL_Rect(30, 74, 4, 10)) };
			break;

		case 16:
		case 17:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(10, 0, 44, 80)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(17, 7, 7, 10)),	
						ShipPart(RIGHT_WEAPON,		SDL_Rect(40, 7, 7, 10)),	
						ShipPart(LEFT_WING,			SDL_Rect(0, 10, 10, 43)),
						ShipPart(RIGHT_WING,		SDL_Rect(54, 10, 10, 43)) };
			break;

		case 18:
		case 19:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(18, 13, 28, 61)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(9, 0, 2, 14)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(53, 0, 2, 14)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 0, 18, 80)),
						ShipPart(RIGHT_WING,		SDL_Rect(46, 0, 18, 80)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(19, 73, 10, 10)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(36, 73, 10, 10)) };
			break;

		case 20:
		case 21:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(16, 0, 32, 79)),
						ShipPart(LEFT_WEAPON,       SDL_Rect(9, 30, 2, 11)),
						ShipPart(RIGHT_WEAPON,      SDL_Rect(53, 30, 2, 11)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 6, 16, 75)),
						ShipPart(RIGHT_WING,		SDL_Rect(48, 6, 16, 75)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(22, 78, 4, 10)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(39, 78, 4, 10)) };
			break;

		case 22:
		case 23:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(20, 0, 24, 57)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(25, 0, 2, 9)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(38, 0, 2, 9)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 13, 20, 67)),
						ShipPart(RIGHT_WING,		SDL_Rect(44, 13, 20, 67)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(23, 57, 7, 10)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(34, 57, 7, 10)) };
			break;

		case 24:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(18, 0, 29, 57)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(25, 0, 2, 9)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(38, 0, 2, 9)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 20, 18, 59)),
						ShipPart(RIGHT_WING,		SDL_Rect(47, 20, 18, 59)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(23, 57, 7, 10)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(34, 57, 7, 10)) };
			break;

		case 25:
		case 26:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(17, 0, 30, 67)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(4, 9, 2, 4)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(59, 9, 2, 4)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 9, 17, 72)),
						ShipPart(RIGHT_WING,		SDL_Rect(47, 9, 17, 72)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(22, 63, 7, 10)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(36, 63, 7, 10)) };
			break;

		case 27:
		case 28:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(23, 0, 19, 61)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(8, 6, 2, 13)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(55, 6, 2, 13)),
						ShipPart(LEFT_WING,			SDL_Rect(1, 6, 22, 74)),
						ShipPart(RIGHT_WING,		SDL_Rect(42, 6, 22, 74)),
						ShipPart(EXHAUST,			SDL_Rect(27, 61, 10, 10)) };
			break;

		case 29:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(24, 0, 16, 72)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(19, 16, 2, 6)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(43, 16, 2, 6)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 35, 13, 44)),
						ShipPart(RIGHT_WING,		SDL_Rect(52, 35, 13, 44)),
						ShipPart(BODY,				SDL_Rect(13, 16, 39, 64)),
						ShipPart(EXHAUST,			SDL_Rect(26, 72, 12, 10)) };
			break;

		case 30:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(15, 0, 35, 80)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(19, 0, 2, 4)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(44, 0, 2, 4)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 24, 15, 41)),
						ShipPart(RIGHT_WING,		SDL_Rect(50, 24, 15, 41)),
						ShipPart(EXHAUST,			SDL_Rect(28, 80, 9, 10)) };
			break;

		case 31:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(14, 0, 37, 80)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(19, 5, 2, 5)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(44, 5, 2, 5)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 24, 14, 57)),
						ShipPart(RIGHT_WING,		SDL_Rect(51, 24, 14, 57)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(20, 80, 9, 10)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(35, 80, 9, 10)) };
			break;

		case 32:
		case 33:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(19, 0, 27, 80)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(3, 24, 2, 6)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(59, 24, 2, 6)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 22, 19, 29)),
						ShipPart(RIGHT_WING,		SDL_Rect(46, 22, 19, 29)),
						ShipPart(EXHAUST,			SDL_Rect(27, 72, 10, 10)) };
			break;

		case 34:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(11, 0, 43, 80)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(16, 8, 2, 12)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(47, 8, 2, 12)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 16, 11, 47)),
						ShipPart(RIGHT_WING,		SDL_Rect(54, 16, 11, 47)),
						ShipPart(EXHAUST,			SDL_Rect(28, 80, 9, 10)) };
			break;

		case 35:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(15, 0, 35, 80)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(6, 11, 4, 17)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(55, 11, 4, 17)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 11, 15, 44)),
						ShipPart(RIGHT_WING,		SDL_Rect(50, 11, 15, 44)),
						ShipPart(EXHAUST,			SDL_Rect(27, 60, 11, 10)) };
			break;

		case 36:
		case 37:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(15, 0, 34, 80)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(1, 16, 2, 6)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(61, 16, 2, 6)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 14, 15, 32)),
						ShipPart(RIGHT_WING,		SDL_Rect(49, 14, 15, 32)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(22, 76, 9, 10)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(34, 76, 9, 10)) };
			break;

		case 38:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(15, 0, 34, 64)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(16, 14, 2, 4)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(46, 14, 2, 4)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 34, 15, 47)),
						ShipPart(RIGHT_WING,		SDL_Rect(49, 39, 15, 47)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(22, 62, 7, 10)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(35, 62, 7, 10)) };
			break;

		case 39:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(22, 0, 20, 80)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(16, 20, 6, 18)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(42, 20, 6, 18)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 21, 22, 57)),
						ShipPart(RIGHT_WING,		SDL_Rect(42, 21, 22, 57)),
						ShipPart(EXHAUST,			SDL_Rect(28, 80, 9, 10)) };
			break;

		case 40:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(23, 0, 18, 80)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(17, 30, 2, 5)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(45, 30, 2, 5)),
						ShipPart(LEFT_WING,			SDL_Rect(12, 30, 11, 50)),
						ShipPart(RIGHT_WING,		SDL_Rect(41, 30, 11, 50)),
						ShipPart(EXHAUST,			SDL_Rect(24, 80, 17, 10)) };
			break;

		case 41:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(20, 0, 25, 80)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(20, 5, 2, 5)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(42, 5, 2, 5)),
						ShipPart(LEFT_WING,			SDL_Rect(8, 20, 12, 54)),
						ShipPart(RIGHT_WING,		SDL_Rect(45, 20, 12, 54)),
						ShipPart(EXHAUST,			SDL_Rect(28, 80, 9, 10)) };
			break;

		case 42:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(21, 0, 24, 80)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(17, 26, 2, 11)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(46, 26, 2, 11)),
						ShipPart(LEFT_WING,			SDL_Rect(14, 26, 7, 23)),
						ShipPart(RIGHT_WING,		SDL_Rect(45, 26, 7, 23)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(21, 80, 10, 10)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(34, 80, 10, 10)) };
			break;

		case 43:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(25, 0, 15, 80)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(17, 29, 2, 3)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(46, 29, 2, 3)),
						ShipPart(LEFT_WING,			SDL_Rect(17, 29, 9, 35)),
						ShipPart(RIGHT_WING,		SDL_Rect(40, 29, 9, 35)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(26, 80, 5, 10)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(35, 80, 5, 10)) };
			break;

		case 44:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(25, 0, 14, 80)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(25, 9, 2, 5)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(37, 9, 2, 5)),
						ShipPart(LEFT_WING,			SDL_Rect(18, 33, 8, 16)),
						ShipPart(RIGHT_WING,		SDL_Rect(39, 33, 8, 16)),
						ShipPart(EXHAUST,			SDL_Rect(26, 80, 13, 10)) };
			break;
			
		case 45:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(22, 0, 21, 80)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(17, 31, 2, 11)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(46, 31, 2, 11)),
						ShipPart(LEFT_WING,			SDL_Rect(15, 31, 7, 29)),
						ShipPart(RIGHT_WING,		SDL_Rect(43, 31, 7, 29)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(24, 80, 5, 10)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(36, 80, 5, 10)) };
			break;

		case 46:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(25, 0, 14, 80)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(21, 36, 2, 5)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(44, 36, 2, 5)),
						ShipPart(LEFT_WING,			SDL_Rect(22, 33, 5, 15)),
						ShipPart(RIGHT_WING,		SDL_Rect(39, 33, 5, 15)),
						ShipPart(EXHAUST,			SDL_Rect(26, 80, 13, 10)) };
			break;

		case 47:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(23, 0, 18, 80)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(15, 26, 2, 9)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(48, 26, 2, 9)),
						ShipPart(LEFT_WING,			SDL_Rect(12, 26, 11, 40)),
						ShipPart(RIGHT_WING,		SDL_Rect(41, 26, 11, 40)),
						ShipPart(EXHAUST,			SDL_Rect(25, 80, 14, 10)) };
			break;
	}

	for (int i = 0; i < m_parts.size(); ++i)
	{
		const SDL_Rect& collider{ m_parts[i].getCollider().getRect() };
		m_parts[i].setOffset(Pair<int>(collider.x, collider.y));
	}

	m_index = index;
}

std::vector<ShipPart>& Ship::getParts()
{
	return m_parts;
}

int Ship::getIndex()
{
	return m_index;
}