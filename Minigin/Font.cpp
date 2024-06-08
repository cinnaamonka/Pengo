#include "Font.h"

#include <SDL_ttf.h>
#include <stdexcept>

TTF_Font* GameEngine::Font::GetFont() const {
	return m_Font;
}

GameEngine::Font::Font(const std::string& fullPath, unsigned int size) : m_Font(nullptr)
{
	m_Font = TTF_OpenFont(fullPath.c_str(), size);
	if (m_Font == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

GameEngine::Font::~Font()
{
	TTF_CloseFont(m_Font);
}
