#pragma once

#include "BaseComponent.h"

namespace GameEngine
{
	class TransformComponent : public BaseComponent
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

