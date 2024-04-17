#include "BlockComponent.h"
#include <TransformComponent.h>
#include <BoxColliderComponent.h>
#include "PushObserver.h"

BlockComponent::BlockComponent(GameEngine::GameObject* pGameObject):
	BaseComponent(pGameObject)  
{

}

void BlockComponent::PushBlock()
{
	auto currentPosition = m_pGameObjectReference->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition(); 

	currentPosition.x += 10 * m_pPushObserver->GetDirection().x; 

	m_pGameObjectReference->GetComponent<GameEngine::TransformComponent>()->SetLocalPosition(currentPosition);
	m_pGameObjectReference->GetComponent<GameEngine::BoxCollider>()->SetBoxCollider(currentPosition);
}
