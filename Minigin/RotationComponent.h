#pragma once
#include "BaseComponent.h"

#include <glm/vec2.hpp>
#include <glm/glm.hpp>

namespace GameEngine
{
	class TransformComponent;

	class RotationComponent : public BaseComponent
	{
	public:
		RotationComponent(GameObject* GOptr, int radius, double speed);

		void Update() override;

	private:
		int m_RotationRadius;
		double m_RotationSpeed;
		glm::vec3 m_RotationCenter;
		double m_CurrentAngle;

		TransformComponent* m_pTransformComponent;
	};
}

