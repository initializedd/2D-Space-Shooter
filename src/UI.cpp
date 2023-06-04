#include "UI.h"
#include "Constants.h"

UI::UI()
	: m_widgets{}
{
}

void UI::createUI()
{
	m_widgets = { Widget(WIDGET_HEALTH,			Vector2<int>(0, 50)),
				  Widget(WIDGET_LIVES,			Vector2<int>(0, 100)),
				  Widget(WIDGET_SHIELD,			Vector2<int>(100, 50)),
				  Widget(WIDGET_WEAPON_UPGRADE, Vector2<int>(100, 100)) };

	m_texture->loadFromFile("img/UI_sprite.png", false);
	m_texture->setClipsFromSprite(110, 111, 40, 4);
}

void UI::render()
{
	for (int i = WIDGET_HEALTH; i < WIDGET_TOTAL; ++i)
	{
		m_texture->render(m_widgets[static_cast<int>(i)].getPos().x, m_widgets[static_cast<int>(i)].getPos().y, &m_texture->getClips()[static_cast<int>(i)], m_texture->getClips()[static_cast<int>(i)].w, m_texture->getClips()[static_cast<int>(i)].h);
	}
}

Texture& UI::getTexture()
{
	return *m_texture;
}