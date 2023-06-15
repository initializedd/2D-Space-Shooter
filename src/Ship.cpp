#include "Ship.h"
#include "Common.h"

Ship::Ship()
	: //m_pos{}
	  m_parts{}
	, m_index{}
	//, m_weapon{}
	, m_exhaustParticle{}
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
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(52 * 0.5, 0 * 0.5, 24 * 0.5, 33 * 0.5)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(42 * 0.5, 32 * 0.5, 4 * 0.5, 20 * 0.5)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(82 * 0.5, 32 * 0.5, 4 * 0.5, 20 * 0.5)),
						ShipPart(WEAPON,			SDL_Rect(25 * 0.5, 32 * 0.5, 78 * 0.5, 21 * 0.5)),
						ShipPart(BODY,				SDL_Rect(0 * 0.5, 52 * 0.5, 128 * 0.5, 89 * 0.5)),
						ShipPart(TAIL,				SDL_Rect(57 * 0.5, 140 * 0.5, 14 * 0.5, 20 * 0.5)) };
			break;

		case 2:
		case 3:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(35, 0, 58, 146)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(25, 49, 12, 15)),		
						ShipPart(RIGHT_WEAPON,		SDL_Rect(91, 49, 12, 15)),		
						ShipPart(LEFT_WING,			SDL_Rect(0, 28, 35, 132)),
						ShipPart(RIGHT_WING,		SDL_Rect(93, 28, 35, 132)) };
			break;

		case 4:
		case 5:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(39, 35, 50, 125)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(36, 53, 4, 14)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(88, 53, 4, 14)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 26, 40, 124)),
						ShipPart(RIGHT_WING,		SDL_Rect(88, 26, 40, 124)), 
						ShipPart(TOP_LEFT_WING,		SDL_Rect(28, 0, 14, 26)),
						ShipPart(TOP_RIGHT_WING,	SDL_Rect(86, 0, 14, 26)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(44, 160, 16, 20)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(68, 160, 16, 20)) };
			break;

		case 6:
		case 7:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(38, 0, 52, 160)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(46, 11, 4, 17)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(78, 11, 4, 17)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 49, 38, 83)),
						ShipPart(RIGHT_WING,		SDL_Rect(90, 49, 38, 83)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(11, 114, 20, 20)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(97, 114, 20, 20)) };
			break;

		case 8:
		case 9:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(32, 0, 64, 160)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(59, 0, 4, 10)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(65, 0, 4, 10)),	
						ShipPart(LEFT_WING,			SDL_Rect(0, 16, 32, 144)),
						ShipPart(RIGHT_WING,		SDL_Rect(96, 16, 32, 144)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(36, 160, 25, 20)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(67, 160, 25, 20)) };
			break;

		case 10:
		case 11:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(42, 0, 44, 147)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(8, 56, 4, 16)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(116, 56, 4, 16)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 56, 42, 104)),
						ShipPart(RIGHT_WING,		SDL_Rect(86, 56, 42, 104)) };
			break;

		case 12:
		case 13:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(27, 27, 57, 130)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(62, 27, 2, 10)),	
						ShipPart(RIGHT_WEAPON,		SDL_Rect(66, 27, 2, 10)),	
						ShipPart(LEFT_WING,			SDL_Rect(0, 0, 27, 160)),
						ShipPart(RIGHT_BODY,		SDL_Rect(84, 3, 23, 139)),
						ShipPart(RIGHT_WING,		SDL_Rect(107, 54, 21, 62)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(47, 157, 28, 20)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(92, 142, 10, 20)) };
			break;

		case 14:
		case 15:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(34, 36, 60, 123)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(47, 36, 4, 18)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(77, 36, 4, 18)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 0, 34, 157)),
						ShipPart(RIGHT_BODY,		SDL_Rect(94, 0, 34, 157)),
						ShipPart(EXHAUST,			SDL_Rect(60, 147, 8, 20)) };
			break;

		case 16:
		case 17:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(20, 0, 88, 160)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(34, 14, 14, 20)),	
						ShipPart(RIGHT_WEAPON,		SDL_Rect(80, 14, 14, 20)),	
						ShipPart(LEFT_WING,			SDL_Rect(0, 20, 20, 86)),
						ShipPart(RIGHT_WING,		SDL_Rect(108, 20, 20, 86)) };
			break;

		case 18:
		case 19:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(36, 25, 56, 122)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(18, 0, 4, 28)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(106, 0, 4, 28)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 0, 36, 160)),
						ShipPart(RIGHT_WING,		SDL_Rect(92, 0, 36, 160)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(37, 146, 20, 20)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(71, 146, 20, 20)) };
			break;

		case 20:
		case 21:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(32, 0, 64, 157)),
						ShipPart(LEFT_WEAPON,       SDL_Rect(18, 59, 4, 21)),
						ShipPart(RIGHT_WEAPON,      SDL_Rect(106, 59, 4, 21)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 11, 32, 149)),
						ShipPart(RIGHT_WING,		SDL_Rect(96, 11, 32, 149)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(43, 156, 7, 20)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(78, 156, 7, 20)) };
			break;

		case 22:
		case 23:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(40, 0, 48, 113)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(49, 0, 4, 17)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(75, 0, 4, 17)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 25, 40, 133)),
						ShipPart(RIGHT_WING,		SDL_Rect(88, 25, 40, 133)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(46, 113, 14, 20)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(68, 113, 14, 20)) };
			break;

		case 24:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(35, 0, 58, 113)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(49, 0, 4, 17)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(75, 0, 4, 17)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 40, 35, 118)),
						ShipPart(RIGHT_WING,		SDL_Rect(93, 40, 35, 118)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(46, 113, 14, 20)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(68, 113, 14, 20)) };
			break;

		case 25:
		case 26:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(34, 0, 60, 133)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(7, 17, 4, 7)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(117, 17, 4, 7)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 17, 34, 143)),
						ShipPart(RIGHT_WING,		SDL_Rect(94, 17, 34, 143)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(43, 126, 13, 20)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(72, 126, 13, 20)) };
			break;

		case 27:
		case 28:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(45, 0, 38, 121)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(15, 11, 4, 25)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(109, 11, 4, 25)),
						ShipPart(LEFT_WING,			SDL_Rect(1, 11, 44, 148)),
						ShipPart(RIGHT_WING,		SDL_Rect(83, 11, 44, 148)),
						ShipPart(EXHAUST,			SDL_Rect(54, 121, 20, 20)) };
			break;

		case 29:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(48, 0, 32, 144)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(38, 32, 4, 11)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(86, 32, 4, 11)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 70, 25, 87)),
						ShipPart(RIGHT_WING,		SDL_Rect(103, 70, 25, 87)),
						ShipPart(BODY,				SDL_Rect(25, 32, 78, 128)),
						ShipPart(EXHAUST,			SDL_Rect(52, 144, 24, 20)) };
			break;

		case 30:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(29, 0, 70, 160)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(37, 0, 4, 7)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(87, 0, 4, 7)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 47, 29, 81)),
						ShipPart(RIGHT_WING,		SDL_Rect(99, 47, 29, 81)),
						ShipPart(EXHAUST,			SDL_Rect(55, 159, 18, 20)) };
			break;

		case 31:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(27, 0, 74, 160)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(37, 9, 4, 9)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(87, 9, 4, 9)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 47, 27, 113)),
						ShipPart(RIGHT_WING,		SDL_Rect(101, 47, 27, 113)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(40, 160, 18, 20)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(70, 160, 18, 20)) };
			break;

		case 32:
		case 33:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(37, 0, 54, 160)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(6, 47, 4, 12)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(118, 47, 4, 12)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 44, 37, 57)),
						ShipPart(RIGHT_WING,		SDL_Rect(91, 44, 37, 57)),
						ShipPart(EXHAUST,			SDL_Rect(54, 144, 20, 20)) };
			break;

		case 34:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(21, 0, 86, 160)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(31, 16, 4, 24)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(93, 16, 4, 24)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 32, 21, 93)),
						ShipPart(RIGHT_WING,		SDL_Rect(107, 32, 21, 93)),
						ShipPart(EXHAUST,			SDL_Rect(55, 160, 18, 20)) };
			break;

		case 35:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(29, 0, 70, 160)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(11, 22, 8, 34)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(109, 22, 8, 34)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 22, 29, 83)),
						ShipPart(RIGHT_WING,		SDL_Rect(99, 22, 29, 83)),
						ShipPart(EXHAUST,			SDL_Rect(53, 119, 22, 20)) };
			break;

		case 36:
		case 37:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(30, 0, 68, 160)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(2, 32, 4, 12)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(122, 32, 4, 12)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 28, 30, 64)),
						ShipPart(RIGHT_WING,		SDL_Rect(98, 28, 30, 64)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(43, 151, 17, 20)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(68, 151, 17, 20)) };
			break;

		case 38:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(30, 0, 68, 127)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(32, 27, 4, 8)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(92, 27, 4, 8)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 67, 30, 93)),
						ShipPart(RIGHT_WING,		SDL_Rect(98, 67, 30, 93)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(44, 124, 14, 20)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(70, 124, 14, 20)) };
			break;

		case 39:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(44, 0, 40, 160)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(32, 40, 12, 36)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(84, 40, 12, 36)),
						ShipPart(LEFT_WING,			SDL_Rect(0, 41, 44, 114)),
						ShipPart(RIGHT_WING,		SDL_Rect(84, 41, 44, 114)),
						ShipPart(EXHAUST,			SDL_Rect(55, 160, 18, 20)) };
			break;

		case 40:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(46, 0, 36, 160)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(34, 59, 4, 10)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(90, 59, 4, 10)),
						ShipPart(LEFT_WING,			SDL_Rect(24, 59, 22, 99)),
						ShipPart(RIGHT_WING,		SDL_Rect(82, 59, 22, 99)),
						ShipPart(EXHAUST,			SDL_Rect(47, 160, 34, 20)) };
			break;

		case 41:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(39, 0, 50, 160)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(40, 9, 4, 9)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(84, 9, 4, 9)),
						ShipPart(LEFT_WING,			SDL_Rect(16, 39, 23, 108)),
						ShipPart(RIGHT_WING,		SDL_Rect(89, 39, 23, 108)),
						ShipPart(EXHAUST,			SDL_Rect(55, 160, 18, 20)) };
			break;

		case 42:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(41, 0, 48, 160)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(34, 51, 4, 21)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(92, 51, 4, 21)),
						ShipPart(LEFT_WING,			SDL_Rect(27, 51, 14, 46)),
						ShipPart(RIGHT_WING,		SDL_Rect(89, 51, 14, 46)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(42, 160, 20, 20)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(68, 160, 20, 20)) };
			break;

		case 43:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(50, 0, 29, 160)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(33, 57, 4, 6)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(92, 57, 4, 6)),
						ShipPart(LEFT_WING,			SDL_Rect(33, 57, 17, 70)),
						ShipPart(RIGHT_WING,		SDL_Rect(79, 57, 17, 70)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(51, 160, 9, 20)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(69, 160, 9, 20)) };
			break;

		case 44:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(50, 0, 28, 160)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(50, 18, 4, 10)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(74, 18, 4, 10)),
						ShipPart(LEFT_WING,			SDL_Rect(35, 66, 15, 31)),
						ShipPart(RIGHT_WING,		SDL_Rect(78, 66, 15, 31)),
						ShipPart(EXHAUST,			SDL_Rect(51, 160, 26, 20)) };
			break;
			
		case 45:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(43, 0, 42, 160)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(33, 62, 4, 21)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(91, 62, 4, 21)),
						ShipPart(LEFT_WING,			SDL_Rect(29, 62, 14, 58)),
						ShipPart(RIGHT_WING,		SDL_Rect(85, 62, 14, 58)),
						ShipPart(LEFT_EXHAUST,		SDL_Rect(47, 160, 9, 20)),
						ShipPart(RIGHT_EXHAUST,		SDL_Rect(72, 160, 9, 20)) };
			break;

		case 46:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(50, 0, 28, 160)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(41, 71, 4, 9)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(83, 71, 4, 9)),
						ShipPart(LEFT_WING,			SDL_Rect(41, 66, 9, 30)),
						ShipPart(RIGHT_WING,		SDL_Rect(78, 66, 9, 30)),
						ShipPart(EXHAUST,			SDL_Rect(51, 160, 26, 20)) };
			break;

		case 47:
			m_parts = { ShipPart(COCKPIT,			SDL_Rect(46, 0, 36, 160)),
						ShipPart(LEFT_WEAPON,		SDL_Rect(29, 52, 4, 18)),
						ShipPart(RIGHT_WEAPON,		SDL_Rect(95, 52, 4, 18)),
						ShipPart(LEFT_WING,			SDL_Rect(24, 52, 22, 80)),
						ShipPart(RIGHT_WING,		SDL_Rect(82, 52, 22, 80)),
						ShipPart(EXHAUST,			SDL_Rect(50, 160, 28, 20)) };
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