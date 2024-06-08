#pragma once
#include "BaseComponent.h" 
#include "Helpers.h"
#include <memory>

#include <glm/glm.hpp>

namespace GameEngine
{
	class TextureComponent;
	class TransformComponent;
	class BlackboardComponent;

	class Texture2D;

	class RenderComponent final: public BaseComponent
	{
	public:
		RenderComponent(GameObject* GOptr);
	
		~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) noexcept = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) noexcept = delete;

		void Render() const override;

		void SetTexture(std::shared_ptr<Texture2D> texture)
		{
			m_Texture = texture;
		}

		void SetPosition(const glm::vec3& pos)
		{
			m_Position = pos;
		}

		const glm::vec3& GetPosition() const
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
		BlackboardComponent* m_pBlackboard;
		AnimationComponent* m_pAnimationComponent;
	};


}
