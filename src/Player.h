#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "PickUp.h"
#include "Ability.h"
#include <sstream>
#include <SDL_events.h>

class Player : public Entity
{
private:
	Ability						m_ability;
	int							m_abilityFrames;
	SDL_Rect*					m_currentAbilityClip;
	bool						m_shieldActivated;

	int							m_flameFrames;
	Texture						m_healthTexture;
	std::stringstream			m_healthText;
	Texture						m_shieldTexture;
	std::stringstream			m_shieldText;

public:
	Player(int x, int y);
	~Player();

	void handleEvent(SDL_Event& event);
	void update(int i, double dt);
	void render();

	void handlePickUpCollision(std::vector<std::unique_ptr<PickUp>>& pickUp);

	bool displayHealth();
	bool displayShield();

	void shieldAnimation();
	void createShield();

	Ability& getAbility();

	void setShield(int shield);
};

#endif // !PLAYER_H