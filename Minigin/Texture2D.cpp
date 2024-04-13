#include <SDL.h>
#include "Texture2D.h"
#include "Renderer.h"


GameEngine::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_texture);
}

glm::ivec2 GameEngine::Texture2D::GetSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

SDL_Texture* GameEngine::Texture2D::CreateCroppedTexture(SDL_Rect srcRect)
{
	srcRect = srcRect;

	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	
	// Get the width and height of the source rectangle
	int width = srcRect.w;
	int height = srcRect.h;

	// Create a surface to hold the cropped texture
	SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	if (!surface)
	{
		// Error handling
		SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
		return nullptr;
	}

	// Clear the surface
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 0, 0, 0, 0));

	// Render the portion of the texture onto the surface
	SDL_Renderer* renderer = Renderer::GetInstance().GetSDLRenderer();
	SDL_Rect destRect = { 0, 0, width, height };
	//SDL_RenderCopy(renderer, GetSDLTexture(), &srcRect, &destRect);

	// Create a new texture from the surface
	SDL_Texture* croppedTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (!croppedTexture)
	{
		// Error handling
		SDL_Log("SDL_CreateTextureFromSurface() failed: %s", SDL_GetError());
		return nullptr;
	}

	// Return the cropped texture
	return croppedTexture; 
}

void GameEngine::Texture2D::RenderTextureToFile(SDL_Texture* texture, const std::string& filename)
{
	// Get the width and height of the texture
	int width{}, height{};
	SDL_QueryTexture(GetSDLTexture(), NULL, NULL, &width, &height);

	if (width <= 0 || height <= 0) {
		// Error handling
		SDL_Log("Invalid texture dimensions: %d x %d", width, height);
		return;
	}

	// Create a surface to hold the rendered texture
	SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	if (!surface)
	{
		// Error handling
		SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
		return;
	}

	// Create a renderer for the surface
	SDL_Renderer* renderer = SDL_CreateSoftwareRenderer(surface);
	if (!renderer)
	{
		// Error handling
		SDL_Log("SDL_CreateSoftwareRenderer() failed: %s", SDL_GetError());
		SDL_FreeSurface(surface);
		return;
	}

	// Clear the surface
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	// Render the texture onto the surface
	SDL_RenderCopy(renderer, texture, NULL, NULL);

	// Save the surface to a file
	if (SDL_SaveBMP(surface, filename.c_str()) != 0)
	{
		// Error handling
		SDL_Log("SDL_SaveBMP() failed: %s", SDL_GetError());
	}

	// Clean up
	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(surface);
}



SDL_Texture* GameEngine::Texture2D::GetSDLTexture() const
{
	return m_texture;
}

GameEngine::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_texture = texture;
}
