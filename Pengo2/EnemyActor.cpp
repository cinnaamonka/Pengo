#include "EnemyActor.h"

#include <TransformComponent.h>
#include <TextureComponent.h>
#include <RenderComponent.h>
#include <BoxColliderComponent.h>
#include <ResourceManager.h>
#include <ActorComponent.h>
#include "HitObserver.h"

EnemyActor::EnemyActor()
{
	m_pEnemy = std::make_unique<GameEngine::GameObject>();
	m_pEnemy->AddComponent<GameEngine::BoxCollider>(200, 200, 20, 20);
	m_pEnemy->AddComponent<GameEngine::TransformComponent>(glm::vec3(200, 300, 0));
	m_pEnemy->AddComponent<GameEngine::TextureComponent>("Enemy.tga");
	m_pEnemy->AddComponent<GameEngine::ActorComponent>();
	m_pEnemy->AddComponent<HitObserver>();
	m_pEnemy->AddComponent<GameEngine::RenderComponent>();
}

std::unique_ptr<GameEngine::GameObject>& EnemyActor::GetActorGameObject()
{
	return m_pEnemy;
}
