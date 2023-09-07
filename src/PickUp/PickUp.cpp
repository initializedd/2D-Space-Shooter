#include "PickUp.h"
#include "../Common/Common.h"
#include <memory>

PickUp::PickUp()
	: m_pos{}
	, m_ability{ HEALTH }
	, m_upgrade{}
	, m_movement{}
	, m_direction{}
{
	m_pos.x = SCREEN_WIDTH / 2;
	m_pos.y = 0;

	m_direction.y = 1;
}

void PickUp::createItem(UpgradeType type)
{
	m_upgrade.type = type;

	switch (type)
	{
		case UPGRADE_HEALTH:
			m_upgrade = { type, SDL_Rect(33 * 0.5 * sf.x, 51 * 0.5 * sf.y, 184 * 0.5 * sf.x, 184 * 0.5 * sf.y) };
			break;

		case UPGRADE_LIVES:
			m_upgrade = { type, SDL_Rect(33 * 0.5 * sf.x, 51 * 0.5 * sf.y, 184 * 0.5 * sf.x, 184 * 0.5 * sf.y) };
			break;

		case UPGRADE_SHIELD:
			m_upgrade = { type, SDL_Rect(33 * 0.5 * sf.x, 51 * 0.5 * sf.y, 184 * 0.5 * sf.x, 184 * 0.5 * sf.y) };
			break;

		case UPGRADE_WEAPON:
			m_upgrade = { type, SDL_Rect(33 * 0.5 * sf.x, 51 * 0.5 * sf.y, 184 * 0.5 * sf.x, 184 * 0.5 * sf.y) };
			break;
	}
}

void PickUp::update(double dt)
{
	m_movement.calculateVelocity(m_direction, 200);
	m_movement.move(m_pos, dt);
	m_upgrade.collider.createColliders(m_pos, 0.0);
}

void PickUp::render()
{
	std::shared_ptr<Sprite> upgrades = resourceManager.getTextureSystem().findSprite("sprite_upgrades");
	upgrades->render
	(
		m_pos.x,
		m_pos.y,
		upgrades->getClips()[m_upgrade.type].w * 0.5 * sf.x,
		upgrades->getClips()[m_upgrade.type].h * 0.5 * sf.y,
		&upgrades->getClips()[m_upgrade.type]
	);

	#if defined(_DEBUG)
	m_upgrade.collider.drawCollider();
	#endif
}

Ability& PickUp::getAbility()
{
	return m_ability;
}

Upgrade& PickUp::getItem()
{
	return m_upgrade;
}