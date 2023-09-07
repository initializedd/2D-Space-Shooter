#ifndef PICK_UP_H
#define PICK_UP_H

#include "../Ability/Ability.h"
#include "../Physics/Movement/Movement.h"
#include "../Physics/Collider/Collider.h"
#include "../Common/Pair.h"
#include <memory>

enum UpgradeType
{
	UPGRADE_HEALTH,
	UPGRADE_LIVES,
	UPGRADE_SHIELD,
	UPGRADE_WEAPON
};

struct Upgrade
{
	UpgradeType						type;
	Collider						collider;
	Vector2<int>					offset;

	Upgrade() = default;
	Upgrade(UpgradeType itemType, SDL_Rect rect) : type{ itemType }, collider{ rect }, offset{ rect.x, rect.y } {}
};

class PickUp
{
private:
	Vector2<float>	m_pos;
	Ability			m_ability;
	Upgrade			m_upgrade;
	Movement		m_movement;
	Vector2<float>	m_direction;

public:
	PickUp();

	void createItem(UpgradeType type);

	void update(double dt);
	void render();

	Ability& getAbility();
	Upgrade& getItem();
};

#endif // !PICK_UP_H