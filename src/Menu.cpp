#include "Menu.h"
#include "Window.h"
#include "Globals.h"

Menu::Menu()
	: m_backgroundTexture{}
	, m_buttons{}
	, m_exitMenu{}
{
}

bool Menu::isQuit()
{
	return m_exitMenu;
}

Texture& Menu::getTexture()
{
	return m_backgroundTexture;
}

std::vector<Button>& Menu::getButtons()
{
	return m_buttons;
}