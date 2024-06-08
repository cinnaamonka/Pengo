#pragma once

#include "BaseComponent.h"
#include <string>

namespace GameEngine
{
	class Texture2D;
	class GameObject;

	class TextureComponent final: public BaseComponent
	{
	public:

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) noexcept = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) noexcept = delete;

		TextureComponent(GameObject* GOptr, const std::string& filename, int textureClipAmount = 1);

		TextureComponent(GameObject* GOptr);

		std::shared_ptr<GameEngine::Texture2D> GetTexture() const;

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<GameEngine::Texture2D>& texture); 

		std::shared_ptr<GameEngine::Texture2D>& GetTexture()
		{
			return m_Texture;
		}
		
		int GetTextureClipAmount() const
		{
			return m_TextureClipAmount;
		}

		void Scale(float scaleX, float scaleY);

		float GetScaleX() const
		{
			return m_ScaleX;
		}
		float GetScaleY() const
		{
			return m_ScaleY;
		}
	private:
		std::shared_ptr<GameEngine::Texture2D> m_Texture;
		std::string fileName;
		int m_TextureClipAmount;

		float m_ScaleX = 1;
		float m_ScaleY = 1;
	};
}


