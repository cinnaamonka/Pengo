#include <Engine.h>

#include "BaseBlock.h"
#include <TransformComponent.h>
#include <TextureComponent.h>
#include <RenderComponent.h>
#include <GameObject.h>
#include <BoxColliderComponent.h>
#include <FSM.h>
#include <memory>
#include <AnimationComponent.h>
#include "BlockObserver.h"

std::unique_ptr<StaticBlockState>          BaseBlock::m_pStaticBlockState = std::make_unique<StaticBlockState>();
std::unique_ptr<BreakingBlockState>        BaseBlock::m_pBreakingBlockState = std::make_unique<BreakingBlockState>();
std::unique_ptr<IsBlockBreaking>           BaseBlock::m_pIsBlockBreaking = std::make_unique<IsBlockBreaking>();
std::unique_ptr<IsBlockNotBreaking>        BaseBlock::m_pIsBlockNotBreaking = std::make_unique<IsBlockNotBreaking>();
std::unique_ptr<FlickeringBlockState>      BaseBlock::m_pFlickeringBlockState = std::make_unique<FlickeringBlockState>();
std::unique_ptr<IsBlockFinishedFlickering> BaseBlock::m_pIsBlockFinishedFlickering = std::make_unique<IsBlockFinishedFlickering>();
std::unique_ptr<VibratingState>            BaseBlock::m_pVibratingBorderState = std::make_unique<VibratingState>();
std::unique_ptr<StopVibrating>             BaseBlock::m_pStopVibratingBorderState = std::make_unique<StopVibrating>();
std::unique_ptr<HasFinishedVibrating>      BaseBlock::m_pHasFinishedVibrating = std::make_unique<HasFinishedVibrating>();
std::unique_ptr<IsVibrating>               BaseBlock::m_pIsVibrating = std::make_unique<IsVibrating>();

BaseBlock::BaseBlock(GameEngine::GameObject* GOptr, int index, BlocksTypes type) :
	GameEngine::BaseComponent(GOptr),
	m_PushSpeed(10),
	m_Position{ 0,0,0 },
	m_ColliderPosition{ 0,0,0 },
	m_BlockIndex(index),
	m_Direction{ 0,0,0 }
	
{
	switch (type)
	{
    case BlocksTypes::Breakable:
        m_IsBreakable = true;
        m_ContainsEggs = false;
        m_IsDiamondBlock = false;
		m_IsHorBorder = false;
		break;
	case BlocksTypes::Diamond:
		m_IsBreakable = false;
		m_ContainsEggs = false;
		m_IsDiamondBlock = true;
		m_IsHorBorder = false;
		break;
	case BlocksTypes::Eggs:
		m_IsBreakable = true;
		m_ContainsEggs = true;
		m_IsDiamondBlock = false;
		m_IsHorBorder = false;
		break;
	case BlocksTypes::BreaksOnSpot:
		m_IsBreakable = true;
		m_IsDiamondBlock = false;
		m_ContainsEggs = false;
		m_ShouldBreakOnSpot = true;
		m_IsHorBorder = false;
		break;
	case BlocksTypes::VerBorder:
		m_IsVerBorder = true;
		m_IsBreakable = false;
		m_IsDiamondBlock = false;
		m_ContainsEggs = false;
		m_ShouldBreakOnSpot = false;
		break;
	case BlocksTypes::HorBorder:
		m_IsHorBorder = true;
		m_IsBreakable = false;
		m_IsDiamondBlock = false;
		m_ContainsEggs = false;
		m_ShouldBreakOnSpot = false;
		break;
	default:
        break;
	}
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
	int index, BlocksTypes type, int clipAmount, int blockSizeX, int blockSizeY, const glm::vec3& colliderBlockPos)
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
	gameObject->AddComponent<GameEngine::AnimationComponent>();
	gameObject->AddComponent<GameEngine::TextureComponent>(filename, clipAmount);
	gameObject->AddComponent<GameEngine::RenderComponent>();
	gameObject->AddComponent<CollisionComponent>();
	gameObject->AddComponent<BaseBlock>(index, type);
	gameObject->AddComponent<HitObserver>();
	gameObject->AddComponent<BlockObserver>();

	bool isBreakable = gameObject->GetComponent<BaseBlock>()->GetIsBreakable();
	bool containsEggs = gameObject->GetComponent<BaseBlock>()->GetContainsEggs();
	bool shouldBreakOnSpot = gameObject->GetComponent<BaseBlock>()->GetShouldBreakOnSpot();
	bool isHorizontalBorder = gameObject->GetComponent<BaseBlock>()->GetHorizontalIsBorder();
	bool isVerticalBorder = gameObject->GetComponent<BaseBlock>()->GetVerticalIsBorder();

	if (isBreakable && !containsEggs)
	{
		gameObject->AddComponent<GameEngine::FSM>(m_pStaticBlockState.get(),
			gameObject->GetComponent<GameEngine::AnimationComponent>());

		gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_pStaticBlockState.get(), m_pBreakingBlockState.get(),
			m_pIsBlockBreaking.get());
		gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_pBreakingBlockState.get(), m_pStaticBlockState.get(),
			m_pIsBlockNotBreaking.get());
	}
	else if (shouldBreakOnSpot)
	{
		gameObject->AddComponent<GameEngine::FSM>(m_pFlickeringBlockState.get(),
			gameObject->GetComponent<GameEngine::AnimationComponent>());

		gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_pFlickeringBlockState.get(), m_pBreakingBlockState.get(),
			m_pIsBlockBreaking.get());
	}
	else if (!containsEggs && !isVerticalBorder && !isHorizontalBorder)
	{
		gameObject->AddComponent<GameEngine::FSM>(m_pStaticBlockState.get(),
			gameObject->GetComponent<GameEngine::AnimationComponent>());
	}
	else if (isVerticalBorder || isHorizontalBorder)
	{
		gameObject->AddComponent<GameEngine::FSM>(m_pStopVibratingBorderState.get(),
			gameObject->GetComponent<GameEngine::AnimationComponent>());

		gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_pStopVibratingBorderState.get(), m_pVibratingBorderState.get(),
			m_pHasFinishedVibrating.get());
		gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_pVibratingBorderState.get(), m_pStopVibratingBorderState.get(),
			m_pIsVibrating.get());

		if (isVerticalBorder)
		{
			gameObject->GetComponent<GameEngine::AnimationComponent>()->SetIsVertical(true);
		}
		else
		{
			gameObject->GetComponent<GameEngine::AnimationComponent>()->SetIsHorizontal(true);
		}
		
	}
	else
	{
		gameObject->AddComponent<GameEngine::FSM>(m_pFlickeringBlockState.get(),
			gameObject->GetComponent<GameEngine::AnimationComponent>());

		gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_pFlickeringBlockState.get(), m_pStaticBlockState.get(),
			m_pIsBlockFinishedFlickering.get());

		gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_pStaticBlockState.get(), m_pBreakingBlockState.get(),
			m_pIsBlockBreaking.get());
		gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_pBreakingBlockState.get(), m_pStaticBlockState.get(),
			m_pIsBlockNotBreaking.get());

	}

	return gameObject;
}

void BaseBlock::Update()
{
	if (m_Pushed)
	{
		auto currentPosition = GetGameObject()->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition();

		currentPosition += static_cast<float>(m_PushSpeed) * m_Direction;

		GetGameObject()->GetComponent<GameEngine::TransformComponent>()->SetLocalPosition(currentPosition);
		GetGameObject()->GetComponent<GameEngine::BoxCollider>()->SetBoxCollider(currentPosition);
	}

}
