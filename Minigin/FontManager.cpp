#include "FontManager.h"
#include "ResourceManager.h"

void GameEngine::FontManager::LoadFont(FontTypes fontType, const std::string& filePath, int size)
{
	auto font = GameEngine::ResourceManager::GetInstance().LoadFont(filePath, size);

	m_pFonts.insert(std::make_pair(fontType, std::make_pair(font, size)));
}
std::shared_ptr<GameEngine::Font> GameEngine::FontManager::GetFont(FontTypes fontType)
{
	auto it = m_pFonts.find(fontType);
	if (it != m_pFonts.end())
	{
		return it->second.first;
	}
	return nullptr;
}