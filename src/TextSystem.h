#ifndef TEXT_SYSTEM_H
#define TEXT_SYSTEM_H

#include "Font.h"
#include "Text.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <SDL_ttf.h>
#include <memory>

class TextSystem
{
private:
	std::unordered_map<std::string, uint32_t>		m_fontIndexByName;
	std::vector<std::shared_ptr<Font>>				m_fonts;

	std::unordered_map<std::string, uint32_t>		m_textIndexByName;
	std::vector<std::shared_ptr<Text>>				m_texts;

	std::unordered_map<std::string, uint32_t>		m_textStreamsIndexByName;
	std::vector<std::shared_ptr<Text>>				m_textStreams;

public:
	TextSystem();
	~TextSystem();

	bool init();

	bool loadFont(const std::string& name, const std::string& path, int ptsize);
	std::shared_ptr<Font> findFont(const std::string& name);

	bool loadText(const std::string& name, const std::string& text);
	std::shared_ptr<Text> findText(const std::string& name);

	bool loadTextStream(const std::string& name);
	std::shared_ptr<Text> findTextStream(const std::string& name);

	std::vector<std::shared_ptr<Font>>& getFonts();
	std::vector<std::shared_ptr<Text>>& getTexts();
	std::vector<std::shared_ptr<Text>>& getTextStreams();
};

#endif // !TEXT_SYSTEM_H