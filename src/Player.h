#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "PickUp.h"
#include "Ability.h"
#include "UI.h"
#include <sstream>
#include <SDL_events.h>
//#include <memory>

class Player : public Entity
{
private:
	Ability						m_ability;
	int							m_abilityFrames;
	SDL_Rect*					m_currentAbilityClip;
	bool						m_shieldActivated;
	bool						m_hasAbility;

	UI							m_ui;

	int							m_flameFrames;
	Texture						m_healthTexture;
	std::stringstream			m_healthText;
	Texture						m_shieldTexture;
	std::stringstream			m_shieldText;

	bool						m_hasSelectedShip;

public:
	Player(int x, int y);
	~Player();

	void handleKeyboardInputs();
	void update(int i, double dt);
	void render();

	void handlePickUpCollision(std::vector<PickUp>& pickUp);

	void healthAnimation();
	void shieldAnimation();

	bool renderHealthAnimation();
	bool renderShieldAnimation();

	bool hasSelectedShip();

	void createHealth();
	void createShield();

	Ability& getAbility();
	UI& getUI();

	void setHasSelectedShip(bool flag);
	void setShield(int shield);
};

#endif // !PLAYER_H