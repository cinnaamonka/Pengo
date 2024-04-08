#include "RotationComponent.h"
#include "TransformComponent.h"
#include "TimeManager.h"

constexpr int twoPI = 360;

GameEngine::RotationComponent::RotationComponent(GameObject* GOptr, int radius, double speed):
	BaseComponent(GOptr),
	m_RotationRadius(radius),
	m_RotationSpeed(speed),
	m_CurrentAngle(0.0),
	m_pTransformComponent(nullptr)
{
	m_pTransformComponent = GetGameObject()->GetComponent<TransformComponent>();
	m_RotationCenter = m_pTransformComponent->GetWorldPosition();
}

void GameEngine::RotationComponent::Update()
{
	const float deltaTime = GameEngine::Time::GetElapsed();

	double angleChange = m_RotationSpeed * deltaTime;

	m_CurrentAngle += angleChange;

	if (m_CurrentAngle > twoPI)
	{
		m_CurrentAngle -= twoPI;
	}

	glm::vec3 newPosition{};

	newPosition.x = static_cast<float>(m_RotationCenter.x + m_RotationRadius * cos(glm::radians(m_CurrentAngle)));
	newPosition.y = static_cast<float>(m_RotationCenter.y + m_RotationRadius * sin(glm::radians(m_CurrentAngle)));
	newPosition.z = m_RotationCenter.z;

	m_pTransformComponent->SetLocalPosition(newPosition);

}
