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
#include <BlackboardComponent.h>

std::unique_ptr<StaticBlockState> BaseBlock::m_pStaticBlockState = std::make_unique<StaticBlockState>();
std::unique_ptr<BreakingBlockState> BaseBlock::m_pBreakingBlockState = std::make_unique<BreakingBlockState>();
std::unique_ptr<IsBlockBreaking> BaseBlock::m_pIsBlockBreaking = std::make_unique<IsBlockBreaking>();
std::unique_ptr<IsBlockNotBreaking> BaseBlock::m_pIsBlockNotBreaking = std::make_unique<IsBlockNotBreaking>();
std::unique_ptr<FlickeringBlockState> BaseBlock::m_pFlickeringBlockState = std::make_unique<FlickeringBlockState>();
std::unique_ptr<IsBlockFinishedFlickering> BaseBlock::m_pIsBlockFinishedFlickering = std::make_unique<IsBlockFinishedFlickering>();

BaseBlock::BaseBlock(GameEngine::GameObject* GOptr, int index, bool isBreakable, bool containsEggs) :
	GameEngine::BaseComponent(GOptr),
	m_PushSpeed(10.0f),
	m_Position{ 0,0,0 },
	m_ColliderPosition{ 0,0,0 },
	m_BlockIndex(index),
	m_IsBreakable(isBreakable),
	m_ContainsEggs(containsEggs),
	m_Direction{ 0,0,0 }
{

}

bool BaseBlock::IsCollidingHorizontally(const GameEngine::Rect& rectShape, GameEngine::HitInfo& hitInfo)
{
	if (GetGameObject()->IsDestroyed() || !GetGameObject())return false;
	return GetGameObject()->GetComponent<GameEngine::BoxCollider>()->IsCollidingHorizontally(rectShape, hitInfo);
}

bool BaseBlock::IsCollidingVertically(const GameEngine::Rect& rectShape, GameEngine::HitInfo& hitInfo)
{
	if (GetGameObject()->IsDestroyed() || !GetGameObject())return false;
	return GetGameObject()->GetComponent<GameEngine::BoxCollider>()->IsCollidingVertically(rectShape, hitInfo);
}

void BaseBlock::PushBlock(const glm::vec3& direction)
{
	m_Direction = direction;
}

std::unique_ptr<GameEngine::GameObject> BaseBlock::CreateBlock(const glm::vec3& position, const std::string& filename,
	int index, bool isBreakable, bool containsEggs, int clipAmount, int blockSizeX, int blockSizeY, const glm::vec3& colliderBlockPos)
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
	gameObject->AddComponent<GameEngine::TextureComponent>(filename, clipAmount);
	gameObject->AddComponent<GameEngine::RenderComponent>();
	gameObject->AddComponent<CollisionComponent>();
	gameObject->AddComponent<BaseBlock>(index, isBreakable, containsEggs);
	gameObject->AddComponent<HitObserver>();
	gameObject->AddComponent<GameEngine::BlackboardComponent>();
	gameObject->AddComponent<AnimationComponent>();
	gameObject->AddComponent<BlockObserver>();

	if (isBreakable && !containsEggs)
	{
		gameObject->AddComponent<GameEngine::FSM>(m_pStaticBlockState.get(),
			gameObject->GetComponent<GameEngine::BlackboardComponent>());

		gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_pStaticBlockState.get(), m_pBreakingBlockState.get(),
			m_pIsBlockBreaking.get());
		gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_pBreakingBlockState.get(), m_pStaticBlockState.get(),
			m_pIsBlockNotBreaking.get());

		gameObject->GetComponent<GameEngine::BlackboardComponent>()->AddData("WasBlockDestroyed", false);
	}
	else if (!containsEggs)
	{
		gameObject->AddComponent<GameEngine::FSM>(m_pStaticBlockState.get(),
			gameObject->GetComponent<GameEngine::BlackboardComponent>());
	}
	else
	{
		gameObject->AddComponent<GameEngine::FSM>(m_pFlickeringBlockState.get(),
			gameObject->GetComponent<GameEngine::BlackboardComponent>());

		gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_pFlickeringBlockState.get(), m_pStaticBlockState.get(),
			m_pIsBlockFinishedFlickering.get());

		gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_pStaticBlockState.get(), m_pBreakingBlockState.get(),
			m_pIsBlockBreaking.get());
		gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_pBreakingBlockState.get(), m_pStaticBlockState.get(),
			m_pIsBlockNotBreaking.get());

		gameObject->GetComponent<GameEngine::BlackboardComponent>()->AddData("AnimationTimes", int());
		gameObject->GetComponent<GameEngine::BlackboardComponent>()->AddData("WasBlockDestroyed", false);

	}

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
