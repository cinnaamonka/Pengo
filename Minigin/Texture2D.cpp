#include <SDL.h>
#include "Texture2D.h"

GameEngine::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

glm::ivec2 GameEngine::Texture2D::GetSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

SDL_Texture* GameEngine::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

GameEngine::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}
