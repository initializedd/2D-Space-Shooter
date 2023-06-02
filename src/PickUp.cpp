#include "PickUp.h"
#include "Constants.h"

PickUp::PickUp()
	: m_pos{}
	, m_ability{SHIELD}
	, m_item{}
	, m_movement{}
	, m_direction{}
{
	m_pos.x = SCREEN_WIDTH / 2;
	m_pos.y = 0;

	m_direction.y = 1;
}

void PickUp::createItem(ItemType type)
{
	m_item.type = type;

	switch(type)
	{
		case ITEM_HEALTH:
			m_item = { type, SDL_Rect(33 * 0.5, 51 * 0.5, 184 * 0.5, 184 * 0.5) };
			break;

		case ITEM_HEART:
			m_item = { type, SDL_Rect(33 * 0.5, 51 * 0.5, 184 * 0.5, 184 * 0.5) };
			break;

		case ITEM_SHIELD:
			m_item = { type, SDL_Rect(33 * 0.5, 51 * 0.5, 184 * 0.5, 184 * 0.5) };
			break;

		case ITEM_AMMO:
			m_item = { type, SDL_Rect(33 * 0.5, 51 * 0.5, 184 * 0.5, 184 * 0.5) };
			break;
	}

	m_item.texture.loadFromFile("img/items_sprite.png", false);
	m_item.texture.setClipsFromSprite(250, 300, 40, 4);
	m_item.texture.scale(m_item.texture.getWidth() * 0.5, m_item.texture.getHeight() * 0.5);
}

void PickUp::update(double dt)
{
	m_movement.calculateVelocity(m_direction, 200);
	m_movement.move(m_pos, dt);
	m_item.collider.setColliders(m_pos, 0.0);
}

void PickUp::render()
{
	m_item.texture.render(m_pos.x, m_pos.y, &m_item.texture.getClips()[m_item.type], m_item.texture.getClips()[m_item.type].w * 0.5, m_item.texture.getClips()[m_item.type].h * 0.5);

	#if defined(_DEBUG)
	m_item.collider.drawCollider();
	#endif
}

Ability& PickUp::getAbility()
{
	return m_ability;
}

Item& PickUp::getItem()
{
	return m_item;
}