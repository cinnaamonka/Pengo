#include <Engine.h>

#include "BaseBlock.h"
#include <TransformComponent.h>
#include <TextureComponent.h>
#include <RenderComponent.h>
#include <GameObject.h>
#include <BoxColliderComponent.h>
#include <FSM.h>
#include <memory>
#include "AnimationComponent.h"
#include "BlockObserver.h"
#include <LifetimeObserver.h>
#include <BlackboardComponent.h>

std::unique_ptr<GameEngine::StaticBlockState> BaseBlock::m_pStaticBlockState = std::make_unique<GameEngine::StaticBlockState>();
std::unique_ptr<GameEngine::BreakingBlockState> BaseBlock::m_pBreakingBlockState = std::make_unique<GameEngine::BreakingBlockState>();
std::unique_ptr<GameEngine::IsBlockBreaking> BaseBlock::m_pIsBlockBreaking = std::make_unique<GameEngine::IsBlockBreaking>();
std::unique_ptr<GameEngine::IsBlockNotBreaking> BaseBlock::m_pIsBlockNotBreaking = std::make_unique<GameEngine::IsBlockNotBreaking>();

BaseBlock::BaseBlock(GameEngine::GameObject* GOptr, int index) :
	GameEngine::BaseComponent(GOptr),
	m_PushSpeed(10.0f),
	m_Position{ 0,0,0 },
	m_ColliderPosition{ 0,0,0 },
	m_pGameObject(nullptr),
	m_BlockIndex(index)
{

}

bool BaseBlock::IsCollidingHorizontally(const GameEngine::Rect& rectShape, GameEngine::HitInfo& hitInfo)
{
	return GetGameObject()->GetComponent<GameEngine::BoxCollider>()->IsCollidingHorizontally(rectShape, hitInfo);
}

bool BaseBlock::IsCollidingVertically(const GameEngine::Rect& rectShape, GameEngine::HitInfo& hitInfo)
{
	return GetGameObject()->GetComponent<GameEngine::BoxCollider>()->IsCollidingVertically(rectShape, hitInfo);
}

void BaseBlock::PushBlock(const glm::vec3& direction)
{
	m_Direction = direction;
}

std::unique_ptr<GameEngine::GameObject> BaseBlock::CreateBlock(const glm::vec3& position, const std::string& filename,
	int index,int blockSizeX, int blockSizeY, const glm::vec3& colliderBlockPos) 
{
	auto gameObject = std::make_unique<GameEngine::GameObject>();

	auto colliderPosition = glm::vec3{ 0,0,0 };

	if (colliderBlockPos == glm::vec3{ 0,0,0 })
	{
		colliderPosition = position;
	}
	else
	{
		colliderPosition = colliderBlockPos;
	}

	gameObject->AddComponent<GameEngine::BoxCollider>(static_cast<int>(colliderPosition.x), static_cast<int>(colliderPosition.y), blockSizeX, blockSizeY);
	gameObject->AddComponent<GameEngine::TransformComponent>(position);
	gameObject->AddComponent<GameEngine::TextureComponent>(filename);
	gameObject->AddComponent<GameEngine::RenderComponent>();
	gameObject->AddComponent<CollisionComponent>();
	gameObject->AddComponent<BaseBlock>(index);
	gameObject->AddComponent<HitObserver>();
	gameObject->AddComponent<GameEngine::LifetimeObserver>();
	gameObject->AddComponent<GameEngine::BlackboardComponent>();
	gameObject->AddComponent<AnimationComponent>();
	gameObject->AddComponent<BlockObserver>(); 

	gameObject->AddComponent<GameEngine::FSM>(m_pStaticBlockState.get(),
		gameObject->GetComponent<GameEngine::BlackboardComponent>());

	gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_pStaticBlockState.get(), m_pBreakingBlockState.get(),
		m_pIsBlockBreaking.get());
	gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_pBreakingBlockState.get(), m_pStaticBlockState.get(),
		m_pIsBlockNotBreaking.get());

	gameObject->GetComponent<GameEngine::BlackboardComponent>()->AddData("WasBlockDestroyed", false);

	return gameObject;
}

void BaseBlock::Update()
{
	if (m_Pushed)
	{
		auto currentPosition = GetGameObject()->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition();

		currentPosition += m_PushSpeed * m_Direction;

		GetGameObject()->GetComponent<GameEngine::TransformComponent>()->SetLocalPosition(currentPosition);
		GetGameObject()->GetComponent<GameEngine::BoxCollider>()->SetBoxCollider(currentPosition);
	}
	
}
