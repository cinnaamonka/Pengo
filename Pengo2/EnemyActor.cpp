#include "EnemyActor.h"

#include <TransformComponent.h>
#include <TextureComponent.h>
#include <RenderComponent.h>
#include <BoxColliderComponent.h>
#include <ResourceManager.h>
#include <ActorComponent.h>
#include "HitObserver.h"
#include "BlackboardComponent.h"

EnemyActor::EnemyActor()
{
	m_pEnemy = std::make_unique<GameEngine::GameObject>();
	m_pEnemy->AddComponent<GameEngine::BoxCollider>(200, 200, 20, 20);
	m_pEnemy->AddComponent<GameEngine::TransformComponent>(glm::vec3(200, 300, 0));
	m_pEnemy->AddComponent<GameEngine::TextureComponent>("Enemy.tga");
	m_pEnemy->AddComponent<GameEngine::ActorComponent>();
	m_pEnemy->AddComponent<HitObserver>();
	m_pEnemy->AddComponent<GameEngine::RenderComponent>();
	m_pEnemy->AddComponent<GameEngine::BlackboardComponent>();

	auto textureSizeX = m_pEnemy->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().x / m_HorizontalAmountOfFrames;
	auto textureSizeY = m_pEnemy->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().y / m_VerticalAmountOfFrames;

	m_pEnemy->GetComponent<GameEngine::TransformComponent>()->SetDimensions({ 0, 0,textureSizeX,textureSizeY });
}

std::unique_ptr<GameEngine::GameObject>& EnemyActor::GetActorGameObject()
{
	return m_pEnemy;
}
