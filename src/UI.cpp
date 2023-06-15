#include "UI.h"
#include "Common.h"

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

//void UI::render()
//{
//	/*for (int i = WIDGET_HEALTH; i < WIDGET_TOTAL; ++i)
//	{
//		m_texture.render(m_widgets[static_cast<int>(i)].getPos().x, m_widgets[static_cast<int>(i)].getPos().y, &m_texture.getClips()[static_cast<int>(i)], m_texture.getClips()[static_cast<int>(i)].w, m_texture.getClips()[static_cast<int>(i)].h);
//	}*/
//
//	// Maybe + 10 to 101 ?
//	double num = 101.0 / 1000;
//	double offset = num * (1000 - health);
//	SDL_Rect rect = SDL_Rect(0, (int)offset, 110, 111 - (int)offset);
//	m_botLayerHealthTexture.render(0, SCREEN_HEIGHT - rect.h, &rect, rect.w, rect.h);
//
//	//SDL_Rect rect = SDL_Rect(0, 45, 110, 66);
//	//m_botLayerTexture.render(0, SCREEN_HEIGHT - 66, &rect, rect.w, rect.h);
//	m_topLayerHealthTexture.render(0, SCREEN_HEIGHT - 111);
//
//	//m_widgets[WIDGET_HEALTH].render();
//
//}

void UI::displayHealth(int health)
{
	double maxHealth = 1000.0;
	double num = 111.0 / maxHealth;
	double offset = num * (maxHealth - health);
	SDL_Rect rect = SDL_Rect(0, (int)offset, 110, 111 - (int)offset);

	std::shared_ptr<Texture> healthInner = resourceManager.getTextureSystem().findTexture("tex_ui_inner_health");
	std::shared_ptr<Texture> healthOuter = resourceManager.getTextureSystem().findTexture("tex_ui_outer_health");

	healthInner->render(0, SCREEN_HEIGHT - rect.h, rect.w, rect.h, &rect);
	healthOuter->render(0, SCREEN_HEIGHT - 111, healthOuter->getWidth(), healthOuter->getHeight(), nullptr);
}

void UI::displayShield(int shield)
{
	double maxShield = 200.0;
	double num = 111.0 / maxShield;
	double offset = num * (maxShield - shield);
	SDL_Rect rect = SDL_Rect(0, (int)offset, 110, 111 - (int)offset);

	std::shared_ptr<Texture> shieldInner = resourceManager.getTextureSystem().findTexture("tex_ui_inner_shield");
	std::shared_ptr<Texture> shieldOuter = resourceManager.getTextureSystem().findTexture("tex_ui_outer_shield");

	shieldInner->render(110, SCREEN_HEIGHT - rect.h, rect.w, rect.h, &rect);
	shieldOuter->render(110, SCREEN_HEIGHT - 111, shieldOuter->getWidth(), shieldOuter->getHeight(), nullptr);
}

std::vector<Widget>& UI::getWidgets()
{
	return m_widgets;
}