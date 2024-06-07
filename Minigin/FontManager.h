#pragma once
#include <string>
#include "Font.h"
#include <unordered_map>
#include <memory>
#include "Singleton.h"

namespace GameEngine
{

	enum class FontTypes
	{
		Small,
		Middle,
		Big
	};


	class FontManager final : public Singleton<FontManager>
	{
	public:
		~FontManager() = default;
		FontManager(const FontManager& other) = delete;
		FontManager(FontManager&& other) = delete;
		FontManager& operator=(const FontManager& other) = delete;
		FontManager& operator=(FontManager&& other) = delete;

		void LoadFont(FontTypes fontType, const std::string& filePath,int size);  
		std::shared_ptr<Font> GetFont(FontTypes fontType);    
	private:
		friend class Singleton<FontManager>; 
		FontManager() = default;
		std::unordered_map < FontTypes, std::pair<std::shared_ptr<Font>,int>> m_pFonts;
	};

}

