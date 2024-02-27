#pragma once
#include "Components.h"

namespace GameEngine
{
	class TextureComponent : public Component
	{
	public:
		TextureComponent(GameObject* GOptr, const std::string& filename);

		TextureComponent(GameObject* GOptr);

		std::shared_ptr<GameEngine::Texture2D> GetTexture() const
		{
			return m_Texture;
		}

		void SetTexture(const std::string& filename)
		{
			m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
		}
		void SetTexture(std::shared_ptr<GameEngine::Texture2D> texture)
		{
			m_Texture = texture;
		}

	private:
		std::shared_ptr<GameEngine::Texture2D> m_Texture;
		std::string fileName;
	};
}


