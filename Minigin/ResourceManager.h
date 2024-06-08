#pragma once

#include <string>
#include <memory>
#include <vector>
#include <SDL_ttf.h>
#include <unordered_map>

#include "Singleton.h"

namespace GameEngine
{
	class Texture2D;
	class Font;

	enum class FontTypes
	{
		Small,
		Middle,
		Big
	};

	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;
		void LoadFontFromFile(FontTypes fontType, const std::string& filePath, int size);
		std::shared_ptr<Font> GetFont(FontTypes fontType) const;
	private:
		std::shared_ptr<GameEngine::Font> LoadFont(const std::string& file, unsigned int size) const;
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_DataPath;
		std::unordered_map <FontTypes, std::pair<std::shared_ptr<Font>, int>> m_pFonts;
	};
}
