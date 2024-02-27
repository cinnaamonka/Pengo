#pragma once
#include "Components.h"
namespace GameEngine
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent(GameObject* GOptr);

		TransformComponent(GameObject* GOptr, glm::vec3 pos);

		const glm::vec3& GetPosition() const
		{
			return m_Position;
		}

		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_Position;
	};
}

