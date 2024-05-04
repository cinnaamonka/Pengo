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
#include "AIMovementComponent.h"
#include "EnemyDirectionObserver.h"
#include "CollisionComponent.h"

#include "FSM.h"

//initialize it
std::unique_ptr<GameEngine::MovingState> EnemyActor::m_RunningState;
std::unique_ptr<GameEngine::AttackState> EnemyActor::m_PushingState;
std::unique_ptr<GameEngine::HasAttacked> EnemyActor::m_IsPengoAttacked;
std::unique_ptr<GameEngine::HasNotAttacked> EnemyActor::m_IsPengoNotAttacked;
std::unique_ptr<PatrolState> EnemyActor::m_MovingState;
std::unique_ptr<ChaseState> EnemyActor::m_ChaseState;
std::unique_ptr<HasNoticedActor> EnemyActor::m_HasNoticedActor;

EnemyActor::EnemyActor()
{

}

std::unique_ptr<GameEngine::GameObject>& EnemyActor::GetActorGameObject()
{
	return m_pEnemy;
}

std::unique_ptr<GameEngine::GameObject> EnemyActor::CreateEnemy()
{
	std::unique_ptr<GameEngine::GameObject> gameObject  = std::make_unique<GameEngine::GameObject>(); 
	 
	gameObject->AddComponent<GameEngine::BoxCollider>(200, 300, 20, 20);
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(200, 300, 0));
	gameObject->AddComponent<GameEngine::TextureComponent>("Enemy.tga");
	gameObject->AddComponent<GameEngine::ActorComponent>();
	gameObject->AddComponent<HitObserver>();
	gameObject->AddComponent<GameEngine::RenderComponent>();
	gameObject->AddComponent<AnimationComponent>();
	gameObject->AddComponent<AIMovementComponent>();
	gameObject->AddComponent<GameEngine::BlackboardComponent>();
	gameObject->AddComponent<EnemyDirectionObserver>();
	

	auto textureSizeX = gameObject->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().x / 8;
	auto textureSizeY = gameObject->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().y / 5;

	gameObject->GetComponent<GameEngine::TransformComponent>()->SetDimensions({ 0, 0,textureSizeX,textureSizeY });

	m_RunningState = std::make_unique<GameEngine::MovingState>();
	m_PushingState = std::make_unique<GameEngine::AttackState>();

	m_IsPengoAttacked = std::make_unique <GameEngine::HasAttacked>();
	m_IsPengoNotAttacked = std::make_unique<GameEngine::HasNotAttacked>();

	gameObject->AddComponent<GameEngine::FSM>(m_RunningState.get(), gameObject->GetComponent<GameEngine::BlackboardComponent>(), "Animation");
	gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_RunningState.get(), m_PushingState.get(), m_IsPengoAttacked.get());
	gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_PushingState.get(), m_RunningState.get(), m_IsPengoNotAttacked.get());

	// DESIGN CHOICE
	// add new state machine and just add new states

	m_MovingState = std::make_unique<PatrolState>();
	m_ChaseState = std::make_unique<ChaseState>();
	m_HasNoticedActor = std::make_unique<HasNoticedActor>();

	gameObject->AddComponent<GameEngine::FSM>(m_MovingState.get(), gameObject->GetComponent<GameEngine::BlackboardComponent>(), "AI");
	gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_MovingState.get(), m_ChaseState.get(), m_HasNoticedActor.get());

	gameObject->GetComponent<GameEngine::BlackboardComponent>()->AddData("Pos", glm::vec3(200, 300, 0));
	gameObject->GetComponent<GameEngine::BlackboardComponent>()->ChangeData("MovementDirection", glm::vec3(1,0,0));

	return gameObject;
}
