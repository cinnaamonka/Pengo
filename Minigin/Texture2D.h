#pragma once
#include <SDL.h>

#include <glm/vec2.hpp>
#include <glm/glm.hpp>

#include <string>

struct SDL_Texture;
namespace GameEngine
{

	class Texture2D final
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		Texture2D(SDL_Texture* texture);
		Texture2D() = default;
		~Texture2D();

		glm::ivec2 GetSize() const;
		// Move constructor
		Texture2D(Texture2D&& other) noexcept
			: m_Texture(other.m_Texture)
		{
			other.m_Texture = nullptr;
		}

	
		Texture2D(const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D& operator=(Texture2D&& other) noexcept
		{
			if (this != &other) // Check for self-assignment
			{
				
				this->m_Texture = other.m_Texture;
				// Reset the source object (optional, but often a good practice)
				other.m_Texture = nullptr;
			}

			return *this;
		}

	private:
		SDL_Texture* m_Texture;
	};
}
