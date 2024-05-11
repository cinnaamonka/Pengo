#include "EnemyActor.h"

#include <TransformComponent.h>
#include <TextureComponent.h>
#include <RenderComponent.h>
#include <BoxColliderComponent.h>
#include "HitObserver.h"
#include "BlackboardComponent.h"
#include "AnimationComponent.h"
#include "AIMovementComponent.h"
#include "EnemyDirectionObserver.h"
#include "CollisionComponent.h"
#include <ActorComponent.h>
#include "PlayerPositionObserver.h"

#include <FSM.h>
#include <AIFSM.h>

std::unique_ptr<MovingState> EnemyActor::m_RunningState			 = std::make_unique<MovingState>();
std::unique_ptr<AttackState> EnemyActor::m_PushingState			 = std::make_unique<AttackState>();
std::unique_ptr<HasAttacked> EnemyActor::m_IsPengoAttacked		 = std::make_unique <HasAttacked>();
std::unique_ptr<HasNotAttacked> EnemyActor::m_IsPengoNotAttacked = std::make_unique<HasNotAttacked>();
std::unique_ptr<PatrolState> EnemyActor::m_MovingState           = std::make_unique<PatrolState>();
std::unique_ptr<ChaseState> EnemyActor::m_ChaseState             = std::make_unique<ChaseState>();
std::unique_ptr<HasNoticedActor> EnemyActor::m_HasNoticedActor   = std::make_unique<HasNoticedActor>();


EnemyActor::EnemyActor(GameEngine::GameObject* pGameObject) :
	BaseComponent(pGameObject),
	m_HasKilledActor(false)
{}

std::unique_ptr<GameEngine::GameObject> EnemyActor::CreateEnemy(glm::vec3& pos,int index)
{
	std::unique_ptr<GameEngine::GameObject> gameObject = std::make_unique<GameEngine::GameObject>();

	gameObject->AddComponent<GameEngine::BoxCollider>(static_cast<int>(pos.x), static_cast<int>(pos.y), 20, 20);
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(static_cast<int>(pos.x), static_cast<int>(pos.y), 0));
	gameObject->AddComponent<GameEngine::TextureComponent>("Enemy.tga");

	gameObject->AddComponent<HitObserver>();
	gameObject->AddComponent<GameEngine::RenderComponent>();
	gameObject->AddComponent<AnimationComponent>();
	gameObject->AddComponent<AIMovementComponent>();
	gameObject->AddComponent<GameEngine::BlackboardComponent>();
	gameObject->AddComponent<EnemyDirectionObserver>(index);
	gameObject->AddComponent<EnemyActor>();
	gameObject->AddComponent<PlayerPositionObserver>();  

	auto textureSizeX = gameObject->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().x / 8;
	auto textureSizeY = gameObject->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().y / 5;

	gameObject->GetComponent<GameEngine::TransformComponent>()->SetDimensions({ 0, 0,textureSizeX,textureSizeY });

	gameObject->AddComponent<GameEngine::FSM>(m_RunningState.get(), gameObject->GetComponent<GameEngine::BlackboardComponent>());
	gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_RunningState.get(), m_PushingState.get(), m_IsPengoAttacked.get());
	gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_PushingState.get(), m_RunningState.get(), m_IsPengoNotAttacked.get());

	gameObject->AddComponent<GameEngine::AIFSM>(m_MovingState.get(), gameObject->GetComponent<GameEngine::BlackboardComponent>());
	gameObject->GetComponent<GameEngine::AIFSM>()->AddTransition(m_MovingState.get(), m_ChaseState.get(), m_HasNoticedActor.get());

	gameObject->GetComponent<GameEngine::BlackboardComponent>()->AddData("Pos", glm::vec3(pos.x, pos.y, 0));
	gameObject->GetComponent<GameEngine::BlackboardComponent>()->AddData("IsChasing", bool());
	gameObject->GetComponent<GameEngine::BlackboardComponent>()->AddData("Speed", 0.3f);

	gameObject->GetComponent<GameEngine::BlackboardComponent>()->ChangeData("MovementDirection", glm::vec3(1, 0, 0));
	

	return gameObject;
}

void EnemyActor::KillPlayer()
{
	m_pPlayer->GetComponent<GameEngine::ActorComponent>()->Damage(1); 
}
