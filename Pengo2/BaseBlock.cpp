#include <Engine.h>

#include "BaseBlock.h"
#include <TransformComponent.h>
#include <TextureComponent.h>
#include <RenderComponent.h>



BaseBlock::BaseBlock(const glm::vec3& position, GameEngine::Scene* scene)
{
	m_pGameObject = std::make_unique<GameEngine::GameObject>();

	m_pGameObject->AddComponent<GameEngine::TransformComponent>(position);
	m_pGameObject->AddComponent<GameEngine::TextureComponent>("IceBlock.tga");
	m_pGameObject->AddComponent<GameEngine::RenderComponent>();

	scene->Add(std::move(m_pGameObject));

}
