#include "TextSystem.h"
#include "Common.h"
#include <SDL_ttf.h>
#include <cstdio>

TextSystem::TextSystem()
	: m_fontIndexByName{}
	, m_fonts{}
	, m_textIndexByName{}
	, m_texts{}
	, m_textStreamsIndexByName{}
	, m_textStreams{}
{
	init();
}

TextSystem::~TextSystem()
{
	m_fonts.clear();
	m_texts.clear();
	m_textStreams.clear();

	TTF_Quit();
}

bool TextSystem::init()
{
	if (TTF_Init() < 0)
	{
		printf("Failed to initialize TTF, Error: %s\n", TTF_GetError());
		return false;
	}

	return true;
}

bool TextSystem::loadFont(const std::string& name, const std::string& path, int ptsize)
{
	static uint32_t index = 0;

	if (m_fontIndexByName.contains(name))
		return false; // already loaded

	std::shared_ptr<Font> font = std::make_shared<Font>();

	if (!font->loadFont(path, ptsize))
		return false;

	m_fonts.push_back(font);

	// Add the fonts name and index so we can search for it later
	m_fontIndexByName.insert(std::pair(name, index));
	++index;

	return true;
}

std::shared_ptr<Font> TextSystem::findFont(const std::string& name)
{
	auto it = m_fontIndexByName.find(name);

	if (it == m_fontIndexByName.end())
	{
		printf("%s does not exist\n", name.c_str());
		return nullptr;
	}

	return m_fonts[it->second];
}

bool TextSystem::loadText(const std::string& name, const std::string& text)
{
	static uint32_t index = 0;

	if (m_textIndexByName.contains(name))
		return false; // already loaded

	std::shared_ptr<Text> txt = std::make_shared<Text>();

	std::shared_ptr<Font> futura = resourceManager.getTextSystem().findFont("ttf_futura");

	if (!txt->loadFromText(text, futura->getFont(), SDL_Color(0xFF, 0xFF, 0xFF, 0xFF)))
		return false;

	m_texts.push_back(txt);

	// Add the fonts name and index so we can search for it later
	m_textIndexByName.insert(std::pair(name, index));
	++index;

	return true;
}

std::shared_ptr<Text> TextSystem::findText(const std::string& name)
{
	auto it = m_textIndexByName.find(name);

	if (it == m_textIndexByName.end())
	{
		printf("%s does not exist\n", name.c_str());
		return nullptr;
	}

	return m_texts[it->second];
}

bool TextSystem::loadTextStream(const std::string& name)
{
	static uint32_t index = 0;

	if (m_textStreamsIndexByName.contains(name))
		return false; // already loaded

	std::shared_ptr<Text> txt = std::make_shared<Text>();

	m_textStreams.push_back(txt);

	// Add the fonts name and index so we can search for it later
	m_textStreamsIndexByName.insert(std::pair(name, index));
	++index;

	return true;
}

std::shared_ptr<Text> TextSystem::findTextStream(const std::string& name)
{
	auto it = m_textStreamsIndexByName.find(name);

	if (it == m_textStreamsIndexByName.end())
	{
		printf("%s does not exist\n", name.c_str());
		return nullptr;
	}

	return m_textStreams[it->second];
}

std::vector<std::shared_ptr<Font>>& TextSystem::getFonts()
{
	return m_fonts;
}

std::vector<std::shared_ptr<Text>>& TextSystem::getTexts()
{
	return m_texts;
}

std::vector<std::shared_ptr<Text>>& TextSystem::getTextStreams()
{
	return m_textStreams;
}