#include "EnemyActor.h"

#include <TransformComponent.h>
#include <TextureComponent.h>
#include <RenderComponent.h>
#include <BoxColliderComponent.h>
#include <AnimationComponent.h>
#include "AIMovementComponent.h"
#include "EnemyDirectionObserver.h"
#include <ActorComponent.h>
#include <SoundServiceLocator.h>
#include "Structs.h"
#include <Texture2D.h>
#include <FSM.h>
#include <AIFSM.h>

std::unique_ptr<PatrolState> EnemyActor::m_MovingState           = std::make_unique<PatrolState>();
std::unique_ptr<ChaseState> EnemyActor::m_ChaseState             = std::make_unique<ChaseState>();
std::unique_ptr<HasNoticedActor> EnemyActor::m_HasNoticedActor   = std::make_unique<HasNoticedActor>();




EnemyActor::EnemyActor(GameEngine::GameObject* pGameObject) :
	BaseComponent(pGameObject),
	m_HasKilledActor(false),
	m_AnimationState{nullptr},
	m_IsKilled(false)
{

}

std::unique_ptr<GameEngine::GameObject> EnemyActor::CreateEnemy(const glm::vec3& pos,int index)
{
	std::unique_ptr<GameEngine::GameObject> gameObject = std::make_unique<GameEngine::GameObject>();

	const int enemySize = 20;

	gameObject->AddComponent<GameEngine::BoxCollider>(static_cast<int>(pos.x), static_cast<int>(pos.y), enemySize, enemySize);
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(static_cast<int>(pos.x), static_cast<int>(pos.y), 0));
	gameObject->AddComponent<GameEngine::TextureComponent>("Enemy.tga");

	gameObject->AddComponent<GameEngine::AnimationComponent>();
	gameObject->AddComponent<GameEngine::RenderComponent>();
	gameObject->AddComponent<AIMovementComponent>();
	gameObject->AddComponent<EnemyDirectionObserver>(index);
	gameObject->AddComponent<EnemyActor>();

	const int textureHorizontalFrames = 8;
	const int textureVerticalFrames = 5;

	auto textureSizeX = gameObject->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().x / textureHorizontalFrames;
	auto textureSizeY = gameObject->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().y / textureVerticalFrames;

	gameObject->GetComponent<GameEngine::TransformComponent>()->SetDimensions({ 0, 0,textureSizeX,textureSizeY });

	gameObject->AddComponent<GameEngine::AIFSM>(m_MovingState.get(), gameObject->GetComponent<GameEngine::AnimationComponent>());
	gameObject->GetComponent<GameEngine::AIFSM>()->AddTransition(m_MovingState.get(), m_ChaseState.get(), m_HasNoticedActor.get());

	gameObject->GetComponent<GameEngine::AnimationComponent>()->SetPos(glm::vec3(pos.x, pos.y, 0));

	const float speed = 0.3f;

	gameObject->GetComponent<GameEngine::AnimationComponent>()->SetSpeed(speed);

	gameObject->GetComponent<GameEngine::AnimationComponent>()->SetMovementDirection(glm::vec3(1, 0, 0));
	

	return gameObject;
}


void EnemyActor::KillPlayer(int killedPlayerIndex)
{
	GameEngine::SoundServiceLocator::GetInstance().GetSoundSystemInstance().Stop(static_cast<int>(PengoSounds::Background));
	m_pPlayers[killedPlayerIndex]->GetComponent<GameEngine::ActorComponent>()->Damage(1);
}

void EnemyActor::Update()
{
	GameEngine::GameObject* gameObject = GetGameObject();  
	m_AnimationState->Update(gameObject);       
}
 
void EnemyActor::HandleInput(IEnemyAnimationState* state) 
{
	m_AnimationState = state;

	GameEngine::GameObject* gameObject = GetGameObject();
	m_AnimationState->HandleInput(gameObject);
}
