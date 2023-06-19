#include "Ability.h"
#include "Common.h"

Ability::Ability(AbilityType type)
	: m_sprite{}
	, m_sound{}
	, m_type{ type }
	, m_value{}
{
}

void Ability::createAbility()
{
	switch (m_type)
	{
		case HEALTH:
			m_value = 200;
			resourceManager.getSoundSystem().findSound("sfx_health_regen")->playChunk(-1, 0, 50);
			break;

		case SHIELD:
			resourceManager.getSoundSystem().findSound("sfx_shield_activate")->playChunk(-1, 0, 50);
			m_value = 300;
			break;

		case RADAR:
			break;
	}
}

Sprite& Ability::getSprite()
{
	return m_sprite;
}

Sound& Ability::getSound()
{
	return m_sound;
}

int Ability::getValue()
{
	return m_value;
}