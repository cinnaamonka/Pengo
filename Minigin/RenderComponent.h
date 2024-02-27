#pragma once
#include "Components.h"

namespace GameEngine
{
	class RenderComponent : public Component
	{
	public:
		RenderComponent(GameObject* GOptr);

		void Render() const override;

		void SetTexture(std::shared_ptr<Texture2D> texture)
		{
			m_Texture = texture;
		}
		void SetPosition(const glm::vec3& pos)
		{
			m_Position = pos;
		}

		glm::vec3 GetPosition() const
		{
			return m_Position;
		}

		std::shared_ptr<Texture2D> GetTexture()
		{
			return m_Texture;
		}

	private:
		std::shared_ptr<Texture2D> m_Texture;
		glm::vec3 m_Position;
		TextureComponent* m_TextureComponent;
		TransformComponent* m_TransformComponent;
	};


}
