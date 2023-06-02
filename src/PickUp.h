#ifndef PICK_UP_H
#define PICK_UP_H

#include "Ability.h"
#include "Movement.h"
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
	Ability			m_ability;
	Item			m_item;
	Movement		m_movement;
	Vector2<float>	m_direction;

public:
	PickUp();

	void createItem(ItemType type);

	void update(double dt);
	void render();

	Ability& getAbility();
	Item& getItem();
};

#endif // !PICK_UP_H