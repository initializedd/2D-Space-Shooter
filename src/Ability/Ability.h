#ifndef ABILITY_H
#define ABILITY_H

#include "../Resource/Sprite/Sprite.h"
#include "../Resource/Sound/Sound.h"

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
	Sprite			m_sprite;
	Sound			m_sound;
	AbilityType		m_type;
	int				m_value;

public:
	Ability() = default;
	Ability(AbilityType type);

	void createAbility();

	Sprite& getSprite();
	Sound& getSound();
	int getValue();
};

#endif // !ABILITY_H