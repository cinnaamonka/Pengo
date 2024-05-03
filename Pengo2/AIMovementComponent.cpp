#include "AIMovementComponent.h"
#include "TransformComponent.h"
#include <FSM.h>

AIMovementComponent::AIMovementComponent(GameEngine::GameObject* pGameObject):
	BaseComponent(pGameObject)
{

}

void AIMovementComponent::Update()
{
	if (GetGameObject()->HasComponent<GameEngine::FSM>())

	{
			glm::vec3 pos;
			GetGameObject()->GetComponent<GameEngine::BlackboardComponent>()->GetData("Pos", pos);
			ChangePosition(pos);
	};
}

void AIMovementComponent::ChangePosition(const glm::vec3& pos)
{
	GetGameObject()->GetComponent<GameEngine::TransformComponent>()->SetLocalPosition(pos); 
}
