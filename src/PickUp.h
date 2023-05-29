#ifndef PICK_UP_H
#define PICK_UP_H

#include "Ability.h"
#include "Collider.h"
#include "Pair.h"

enum ItemType
{
	ITEM_HEALTH,
	ITEM_HEART,
	ITEM_SHIELD,
	ITEM_AMMO
};

struct Item
{
	ItemType		type;
	Collider		collider;
	Vector2<int>	offset;
	Texture			texture;

	Item() = default;
	Item(ItemType itemType, SDL_Rect rect) : type{ itemType }, collider{ rect }, offset{ rect.x, rect.y }, texture{} {}
};

class PickUp
{
private:
	Vector2<float>	m_pos;
	Vector2<float>	m_vel;
	Ability			m_ability;
	Item			m_item;

public:
	PickUp();

	void createItem(ItemType type);

	void move();

	Item& getItem();
};

#endif // !PICK_UP_H