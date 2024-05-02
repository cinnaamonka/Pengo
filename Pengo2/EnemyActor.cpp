#include "EnemyActor.h"

#include <TransformComponent.h>
#include <TextureComponent.h>
#include <RenderComponent.h>
#include <BoxColliderComponent.h>
#include <ResourceManager.h>
#include <ActorComponent.h>
#include "HitObserver.h"
#include "BlackboardComponent.h"
#include "AnimationComponent.h"

#include "FSM.h"

EnemyActor::EnemyActor()
{
	m_pEnemy = std::make_unique<GameEngine::GameObject>();
	m_pEnemy->AddComponent<GameEngine::BoxCollider>(200, 300, 20, 20);
	m_pEnemy->AddComponent<GameEngine::TransformComponent>(glm::vec3(200, 300, 0));
	m_pEnemy->AddComponent<GameEngine::TextureComponent>("Enemy.tga");
	m_pEnemy->AddComponent<GameEngine::ActorComponent>();
	m_pEnemy->AddComponent<HitObserver>();
	m_pEnemy->AddComponent<GameEngine::RenderComponent>();
	m_pEnemy->AddComponent<AnimationComponent>();
	m_pEnemy->AddComponent<GameEngine::BlackboardComponent>();

	auto textureSizeX = m_pEnemy->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().x / m_HorizontalAmountOfFrames;
	auto textureSizeY = m_pEnemy->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().y / m_VerticalAmountOfFrames;

	m_pEnemy->GetComponent<GameEngine::TransformComponent>()->SetDimensions({ 0, 0,textureSizeX,textureSizeY });

	m_RunningState = std::make_unique<GameEngine::MovingState>();
	m_PushingState = std::make_unique<GameEngine::AttackState>();

	m_IsPengoAttacked = std::make_unique <GameEngine::HasAttacked>();
	m_IsPengoNotAttacked = std::make_unique<GameEngine::HasNotAttacked>();

	m_pEnemy->AddComponent<GameEngine::FSM>(m_RunningState.get(), m_pEnemy->GetComponent<GameEngine::BlackboardComponent>(),"Animation");
	m_pEnemy->GetComponent<GameEngine::FSM>()->AddTransition(m_RunningState.get(), m_PushingState.get(), m_IsPengoAttacked.get());
	m_pEnemy->GetComponent<GameEngine::FSM>()->AddTransition(m_PushingState.get(), m_RunningState.get(), m_IsPengoNotAttacked.get());


	// DESIGN CHOICE
	// add new state machine and just add new states

	m_MovingState = std::make_unique<PatrolState>(); 
	m_ChaseState = std::make_unique<ChaseState>();
	m_HasNoticedActor = std::make_unique<HasNoticedActor>();

	m_pEnemy->AddComponent<GameEngine::FSM>(m_MovingState.get(), m_pEnemy->GetComponent<GameEngine::BlackboardComponent>(),"AI");
	m_pEnemy->GetComponent<GameEngine::FSM>()->AddTransition(m_MovingState.get(), m_ChaseState.get(), m_HasNoticedActor.get());
}

std::unique_ptr<GameEngine::GameObject>& EnemyActor::GetActorGameObject()
{
	return m_pEnemy;
}
