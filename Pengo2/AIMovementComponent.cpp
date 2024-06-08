#include "AIMovementComponent.h"
#include "TransformComponent.h"
#include <FSM.h>

AIMovementComponent::AIMovementComponent(GameEngine::GameObject* pGameObject) :
	BaseComponent(pGameObject)
{
	m_pAnimationComponent = GetGameObject()->GetComponent<GameEngine::AnimationComponent>();
	m_pTranformComponent = GetGameObject()->GetComponent<GameEngine::TransformComponent>();
}

void AIMovementComponent::Update()
{

	glm::vec3 pos = m_pAnimationComponent->GetPos();

	ChangePosition(pos);

}

void AIMovementComponent::ChangePosition(const glm::vec3& pos)
{
	m_pTranformComponent->SetLocalPosition(pos);
}
