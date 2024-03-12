#pragma once

#include "BaseComponent.h" 

#include <memory>

#include <glm/vec2.hpp>
#include <glm/glm.hpp>

namespace GameEngine
{
	class TextureComponent;
	class TransformComponent;
	class Texture2D;

	class RenderComponent : public BaseComponent
	{
	public:
		RenderComponent(GameObject* GOptr);

		virtual void Render() override;

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
