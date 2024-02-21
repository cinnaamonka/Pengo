#pragma once
#include <glm/vec2.hpp>

struct SDL_Texture;
namespace dae
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D final
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		explicit Texture2D(SDL_Texture* texture);
		~Texture2D();

		glm::ivec2 GetSize() const;

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D& operator=(Texture2D&& other)
		{
			if (this != &other) // Check for self-assignment
			{
				// Implement the move assignment logic here
				// Make sure to properly move the data members from 'other' to 'this'

				// If your class contains pointers or resources, move them here

				// For demonstration purposes, let's assume 'm_texture' is a pointer:
				// Replace this line with your actual data members' moves.
				// Example:
				// this->m_texture = other.m_texture;
				this->m_texture = other.m_texture;
				// Reset the source object (optional, but often a good practice)
				other.m_texture = nullptr;
			}

			return *this;
		}
	private:
		SDL_Texture* m_texture;
	};
}
