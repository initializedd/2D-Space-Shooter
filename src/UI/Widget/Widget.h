#ifndef WIDGET_H
#define WIDGET_H

#include "../../Resource/Texture/Texture.h"
#include "../../Common/Pair.h"
#include <string>

enum WidgetType
{
	WIDGET_HEALTH,
	WIDGET_LIVES,
	WIDGET_SHIELD,
	WIDGET_WEAPON_UPGRADE,
	WIDGET_TOTAL
};

class Widget
{
private:
	WidgetType				m_type;
	Vector2<int>			m_pos;

public:
	Widget(WidgetType type, Vector2<int> pos);

	Vector2<int> getPos() const;
	WidgetType getType();
};

#endif // !WIDGET_H