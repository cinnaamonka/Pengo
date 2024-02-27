#pragma once

struct SDL_Texture;
namespace GameEngine
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
		Texture2D& operator=(Texture2D&& other) noexcept
		{
			if (this != &other) // Check for self-assignment
			{
				
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
