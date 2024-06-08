#pragma once

#include "BaseComponent.h"

#include <glm/glm.hpp>

#include "Helpers.h"

namespace GameEngine
{
	class BoxCollider;

	class TransformComponent : public BaseComponent
	{
	public:
		TransformComponent(GameObject* GOptr);
		TransformComponent(GameObject* GOptr, glm::vec3 pos);

		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) noexcept = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) noexcept = delete;
		~TransformComponent() = default;

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

		glm::vec3 GetWorldPosition();

		bool IsPositionDirty() const
		{
			return m_IsPositionDirty;
		}
		
		void UpdateWorldPosition();

		const Rect& GetDimensions() const
		{
			return m_DestDimensions;
		}

		void SetDimensions(const Rect& dimensions)
		{
			m_DestDimensions = dimensions;
		}

	private:
		void SetPositionDirty();
	private:

		glm::vec3 m_LocalPosition;
		glm::vec3 m_WorldPosition;

		bool m_IsPositionDirty;

		BoxCollider* m_pBoxCollider;

		Rect m_DestDimensions;

	};
}

