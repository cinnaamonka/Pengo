#include <Engine.h>

#include "BaseBlock.h"
#include <TransformComponent.h>
#include <TextureComponent.h>
#include <RenderComponent.h>
#include <BoxColliderComponent.h>


BaseBlock::BaseBlock(const glm::vec3& position, GameEngine::Scene* scene):
	m_BlockSize(20)
{
	m_pGameObject = std::make_unique<GameEngine::GameObject>();

	int xPos = static_cast<int>(position.x);
	int yPos = static_cast<int>(position.y);

	m_pGameObject->AddComponent<GameEngine::BoxCollider>(xPos, yPos, m_BlockSize, m_BlockSize);

	m_pGameObject->AddComponent<GameEngine::TransformComponent>(position);
	m_pGameObject->AddComponent<GameEngine::TextureComponent>("IceBlock.tga");
	m_pGameObject->AddComponent<GameEngine::RenderComponent>();

	
	

	scene->Add(std::move(m_pGameObject));

}

bool BaseBlock::IsColliding(const Rect& rectShape,HitInfo& hitInfo) const
{
	return m_pGameObject->GetComponent<GameEngine::BoxCollider>()->IsColliding(rectShape, hitInfo);
}
