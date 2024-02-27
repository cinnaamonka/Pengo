#pragma once

#include "BaseComponent.h"

namespace GameEngine
{
	class TransformComponent : public BaseComponent
	{
	public:
		TransformComponent(GameObject* GOptr);

		TransformComponent(GameObject* GOptr, glm::vec3 pos);

		void SetLocalPosition(float x, float y, float z);
		void SetLocalPosition(const glm::vec3& position);

		void SetWorldPosition(float x, float y, float z);
		void SetWorldPosition(const glm::vec3& position);

		void Translate(float x, float y, float z);
		void Translate(const glm::vec3& translation);

		glm::vec3 GetLocalPosition() const
		{
			return m_LocalPosition;
		}

		glm::vec3 GetWorldPosition() const
		{
			return m_WorldPosition;
		}

	private:

		glm::vec3 m_LocalPosition;
		glm::vec3 m_WorldPosition;
	};
}

