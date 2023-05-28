#include "Ability.h"

Ability::Ability(AbilityType type)
	: m_particle{}
	, m_sound{}
	, m_type{ type }
	, m_value{}
{
}

void Ability::createAbility()
{
	switch (m_type)
	{
		case SHIELD:
			//m_particle.getTexture().loadFromFile("img/front_shield_sprite.png", false);
			//m_particle.setClipsFromSprite(512, 512, 40, 16);
			//m_sound.loadChunk("audio/front_shield_on.mp3");
			//m_sound.loadChunk("audio/front_shield_off.mp3");
			m_value = 300;
			break;

		case RADAR:
			break;
	}
}

int Ability::getValue()
{
	return m_value;
}