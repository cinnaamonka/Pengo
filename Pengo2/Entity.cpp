#include "Entity.h"

#include <TransformComponent.h>
#include <TextureComponent.h>
#include <RenderComponent.h>
#include <BoxColliderComponent.h>
#include <ResourceManager.h>
#include <ActorComponent.h>
#include "HitObserver.h"

Entity::Entity(const std::string& filePath, const glm::vec3& pos)
{
	m_pActor = std::make_unique<GameEngine::GameObject>();
	m_pActor->AddComponent<GameEngine::BoxCollider>(pos.x, pos.y, 20, 20);
	m_pActor->AddComponent<GameEngine::TransformComponent>(glm::vec3(pos.x, pos.y, 0));
	m_pActor->AddComponent<GameEngine::TextureComponent>(filePath);
	m_pActor->AddComponent<GameEngine::ActorComponent>();
	m_pActor->AddComponent<HitObserver>();
	m_pActor->AddComponent<GameEngine::RenderComponent>();
}

std::unique_ptr<GameEngine::GameObject>& Entity::GetActorGameObject()
{
	return m_pActor;
}
