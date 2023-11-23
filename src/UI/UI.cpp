#include "UI.h"
#include "../Common/Common.h"

UI::UI()
	: m_widgets{}
{
}

void UI::createUI()
{
	m_widgets = { Widget(WIDGET_HEALTH,			Vector2<int>(0, SCREEN_HEIGHT - 111)),
				  Widget(WIDGET_LIVES,			Vector2<int>(0, 100)),
				  Widget(WIDGET_SHIELD,			Vector2<int>(150, SCREEN_HEIGHT - 111)),
				  Widget(WIDGET_WEAPON_UPGRADE, Vector2<int>(100, 100)) };
}

void UI::displayHealth(int health)
{
	double maxHealth = 1000.0;
	double num = 111.0 / maxHealth;
	double offset = num * (maxHealth - health);
	SDL_FRect rect{ 0.f, static_cast<float>(offset), 110.f, 111.f - static_cast<float>(offset) };

	std::shared_ptr<Texture> healthInner = resourceManager.getTextureSystem().findTexture("tex_ui_inner_health");
	std::shared_ptr<Texture> healthOuter = resourceManager.getTextureSystem().findTexture("tex_ui_outer_health");

	healthInner->render(0, SCREEN_HEIGHT - rect.h * sf.y, rect.w * sf.x, rect.h * sf.y, &rect);
	healthOuter->render(0, SCREEN_HEIGHT - 111 * sf.y, healthOuter->getWidth() * sf.x, healthOuter->getHeight() * sf.y, nullptr);
}

void UI::displayShield(int shield)
{
	double maxShield = 200.0;
	double num = 111.0 / maxShield;
	double offset = num * (maxShield - shield);
	SDL_FRect rect{ 0, static_cast<float>(offset), 110.f, 111.f - static_cast<float>(offset) };

	std::shared_ptr<Texture> shieldInner = resourceManager.getTextureSystem().findTexture("tex_ui_inner_shield");
	std::shared_ptr<Texture> shieldOuter = resourceManager.getTextureSystem().findTexture("tex_ui_outer_shield");

	shieldInner->render(110 * sf.x, SCREEN_HEIGHT - rect.h * sf.y, rect.w * sf.x, rect.h * sf.y, &rect);
	shieldOuter->render(110 * sf.x, SCREEN_HEIGHT - 111 * sf.y, shieldOuter->getWidth() * sf.x, shieldOuter->getHeight() * sf.y, nullptr);
}

std::vector<Widget>& UI::getWidgets()
{
	return m_widgets;
}
