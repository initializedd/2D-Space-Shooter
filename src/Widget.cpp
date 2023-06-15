#include "Widget.h"
#include "Common.h"

Widget::Widget(WidgetType type, Vector2<int> pos)
	: m_type{type}
	, m_pos{pos}
{
}

Vector2<int> Widget::getPos() const
{
	return m_pos;
}

WidgetType Widget::getType()
{
	return m_type;
}
