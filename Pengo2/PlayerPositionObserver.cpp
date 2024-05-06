#include "PlayerPositionObserver.h"
#include <TransformComponent.h>
#include <BlackboardComponent.h>

PlayerPositionObserver::PlayerPositionObserver(GameEngine::GameObject* pGameObject):
	BaseComponent(pGameObject),
	m_Radius(20)
{
}

void PlayerPositionObserver::Notify(const glm::vec3& message_from_subject)
{
	const auto currentEnemyPosition = GetGameObject()->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition();

	const auto distance = glm::distance(message_from_subject, currentEnemyPosition); 

	const auto newDirection = message_from_subject - currentEnemyPosition;

	if (distance < m_Radius && AreOnSameLine({ 0,0,0 },message_from_subject, currentEnemyPosition))
	{
		GetGameObject()->GetComponent<GameEngine::BlackboardComponent>()->ChangeData("IsChasing", true);  
		GetGameObject()->GetComponent<GameEngine::BlackboardComponent>()->ChangeData("MovementDirection", newDirection); 
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

		// Check if the direction vectors are collinear
		return AreVectorsCollinear(dirVector1, dirVector2,1.0f); 
	
}
