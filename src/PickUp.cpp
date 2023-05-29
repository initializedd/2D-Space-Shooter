#include "PickUp.h"

PickUp::PickUp()
	: m_pos{}
	, m_vel{}
	, m_ability{SHIELD}
{
}

void PickUp::createItem(ItemType type)
{
	switch(type)
	{
		case ITEM_HEALTH:
			m_item = { type, SDL_Rect(53, 71, 184, 184) };
			break;

		case ITEM_HEART:
			m_item = { type, SDL_Rect(343, 71, 184, 184) };
			break;

		case ITEM_SHIELD:
			m_item = { type, SDL_Rect(633, 71, 184, 184) };
			break;

		case ITEM_AMMO:
			m_item = { type, SDL_Rect(923, 71, 184, 184) };
			break;
	}

	m_item.texture.loadFromFile("img/items_sprite.png", false);
	m_item.texture.setClipsFromSprite(250, 300, 40, 4);
}

Item& PickUp::getItem()
{
	return m_item;
}