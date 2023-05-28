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
			m_particle.getTexture().loadFromFile("img/blue_shield_sprite.png", false);
			m_particle.getTexture().setClipsFromSprite(340, 340, 40, 11);
			//m_sound.loadChunk("audio/front_shield_on.mp3");
			//m_sound.loadChunk("audio/front_shield_off.mp3");
			m_value = 300;
			break;

		case RADAR:
			break;
	}
}

Particle& Ability::getParticle()
{
	return m_particle;
}

Sound& Ability::getSound()
{
	return m_sound;
}

int Ability::getValue()
{
	return m_value;
}