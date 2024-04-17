#include <Engine.h>

#include "BaseBlock.h"
#include <TransformComponent.h>
#include <TextureComponent.h>
#include <RenderComponent.h>
#include <BoxColliderComponent.h>


BaseBlock::BaseBlock(const glm::vec3& position, GameEngine::Scene* scene, const std::string& filename) :
	m_BlockSize(20), m_pBoxCollider(nullptr), m_Position(position)
{
	m_pGameObject = std::make_unique<GameEngine::GameObject>();

	int xPos = static_cast<int>(position.x);
	int yPos = static_cast<int>(position.y);

	
	m_pGameObject->AddComponent<GameEngine::BoxCollider>(xPos, yPos, m_BlockSize, m_BlockSize);
	m_pGameObject->AddComponent<GameEngine::TransformComponent>(position);
	m_pGameObject->AddComponent<GameEngine::TextureComponent>(filename);
	m_pGameObject->AddComponent<GameEngine::RenderComponent>();
	
	m_pBoxCollider = m_pGameObject->GetComponent<GameEngine::BoxCollider>();

	m_pGameObjectReference = m_pGameObject.get();

	scene->Add(std::move(m_pGameObject));
}

bool BaseBlock::IsCollidingHorizontally(const GameEngine::Rect& rectShape, GameEngine::HitInfo& hitInfo)
{
	return m_pBoxCollider->IsCollidingHorizontally(rectShape, hitInfo);
}

bool BaseBlock::IsCollidingVertically(const GameEngine::Rect& rectShape, GameEngine::HitInfo& hitInfo)
{
	return m_pBoxCollider->IsCollidingVertically(rectShape, hitInfo);
}

void BaseBlock::PushBlock(const glm::vec3& direction)
{
	auto currentPosition = m_pGameObjectReference->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition();

	currentPosition.x += 10 * direction.x;

	m_pGameObjectReference->GetComponent<GameEngine::TransformComponent>()->SetLocalPosition(currentPosition);
	m_pGameObjectReference->GetComponent<GameEngine::BoxCollider>()->SetBoxCollider(currentPosition);
}
