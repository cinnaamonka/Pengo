#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

#include <SDL_image.h>
#include <stdexcept>


void GameEngine::ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<GameEngine::Texture2D> GameEngine::ResourceManager::LoadTexture(const std::string& file) const
{
	const auto fullPath = m_DataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_shared<Texture2D>(texture);
}

void GameEngine::ResourceManager::LoadFontFromFile(FontTypes fontType, const std::string& filePath, int size)
{
	auto font = GameEngine::ResourceManager::GetInstance().LoadFont(filePath, size);

	m_pFonts.insert(std::make_pair(fontType, std::make_pair(font, size)));
}

std::shared_ptr<GameEngine::Font> GameEngine::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return std::make_shared<Font>(m_DataPath + file, size);
}

std::shared_ptr<GameEngine::Font> GameEngine::ResourceManager::GetFont(FontTypes fontType) const
{
	auto it = m_pFonts.find(fontType);
	if (it != m_pFonts.end())
	{
		return it->second.first;
	}
	return nullptr;
}