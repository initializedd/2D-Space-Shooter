#ifndef ABILITY_H
#define ABILITY_H

#include "Particle.h"
#include "Sound.h"

enum AbilityType
{
	HEALTH,
	LIFE,
	SHIELD,
	RADAR
};

class Ability
{
private:
	Particle		m_particle;
	Sound			m_sound;
	AbilityType		m_type;
	int				m_value;

public:
	Ability() = default;
	Ability(AbilityType type);

	void createAbility();

	Particle& getParticle();
	Sound& getSound();
	int getValue();
};

#endif // !ABILITY_H