#pragma once
#include "BaseComponent.h"

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

