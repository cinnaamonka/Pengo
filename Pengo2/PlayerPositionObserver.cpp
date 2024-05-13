#include "PlayerPositionObserver.h"
#include <TransformComponent.h>
#include <AnimationComponent.h>
#include "EnemyActor.h"

PlayerPositionObserver::PlayerPositionObserver(GameEngine::GameObject* pGameObject) :
	BaseComponent(pGameObject),
	m_Radius(20)
{
}

void PlayerPositionObserver::Notify(const glm::vec3& message_from_subject)
{
	const auto currentEnemyPosition = GetGameObject()->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition();

	if (AreNear(message_from_subject, currentEnemyPosition,5.0f))
	{
		GetGameObject()->GetComponent<EnemyActor>()->KillPlayer();
		GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->SetMovementDirection(glm::vec3{0.0f,0.0f,0.0f});
		return;
	}

	const auto distance = glm::distance(message_from_subject, currentEnemyPosition);

	const auto newDirection = message_from_subject - currentEnemyPosition;

	if (distance < m_Radius && AreOnSameLine({ 0,0,0 }, message_from_subject, currentEnemyPosition))
	{
		GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->SetIsChasing(true);
		GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->SetMovementDirection(newDirection);
	}
}

bool PlayerPositionObserver::AreVectorsCollinear(const glm::vec3& v1, const glm::vec3& v2, float tolerance) const
{
	auto length = glm::length(glm::normalize(glm::cross(v1, v2)));
	return length < tolerance;
}

bool PlayerPositionObserver::AreOnSameLine(const glm::vec3& referencePoint, const glm::vec3& pos1, const glm::vec3& pos2) const
{
	glm::vec3 dirVector1 = pos1 - referencePoint;
	glm::vec3 dirVector2 = pos2 - referencePoint;

	return AreVectorsCollinear(dirVector1, dirVector2, 1.0f);

}
bool PlayerPositionObserver::AreNear(const glm::vec3& pos1, const glm::vec3& pos2, float threshold) 
{
	float distance = glm::distance(pos1, pos2);
	return distance <= threshold;
}
