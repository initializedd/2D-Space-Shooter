#include "Widget.h"

Widget::Widget(WidgetType type, Vector2<int> pos)
	: m_type{type}
	, m_pos{pos}
	, m_texture{}
	, m_text{}
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