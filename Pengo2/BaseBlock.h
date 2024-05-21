#pragma once
#include <memory>
#include <GameObject.h>
#include <BaseComponent.h>
#include <Helpers.h>
#include <BoxColliderComponent.h>
#include "BlocksStatesAndTransitions.h"
#include "BorderStatesAndTransirions.h"
#include <Scene.h>
#include "Structs.h"
#include "HitObserver.h"
#include "CollisionComponent.h"

class BoxCollider;
class HitObserver;

class BaseBlock final : public GameEngine::BaseComponent
{
public:
	BaseBlock(GameEngine::GameObject* GOptr, int index, BlocksTypes type);
	~BaseBlock() = default;

	BaseBlock(const BaseBlock& other) = delete;
	BaseBlock& operator=(const BaseBlock& other) = delete;
	BaseBlock(BaseBlock&& other) noexcept = delete;
	BaseBlock& operator=(BaseBlock&& other) noexcept = delete;

	bool IsCollidingHorizontally(const GameEngine::Rect& rectShape, GameEngine::HitInfo& hitInfo);
	bool IsCollidingVertically(const GameEngine::Rect& rectShape, GameEngine::HitInfo& hitInfo);

	void PushBlock(const glm::vec3& direction);

	const glm::vec3& GetPosition()
	{
		return m_Position;
	}

	void SetPushSpeed(float speed)
	{
		m_PushSpeed = speed;
	}

	const float GetPushSpeed() const
	{
		return m_PushSpeed;
	}

	static std::unique_ptr<GameEngine::GameObject> CreateBlock(const glm::vec3& position, const std::string& filename, int index,
		BlocksTypes types,int clipAmount = 1,int blockSizeX = 20, int blockSizeY = 20,
		const glm::vec3& colliderBlockPos = glm::vec3{ 0,0,0 });

	int GetBlockIndex() const
	{
		return m_BlockIndex;
	}

	void SetBlockIndex(int index)
	{
		m_BlockIndex = index;
	}

	void SetIsPushed(bool pushed)
	{
		m_Pushed = pushed;
	}

	bool GetIsPushed() const
	{
		return m_Pushed;
	}

	void Update() override;

	const glm::vec3& GetDirection() const
	{
		return m_Direction;
	}

	bool GetIsBreakable() const
	{
		return m_IsBreakable;
	}

	bool GetContainsEggs() const
	{
		return m_ContainsEggs;
	}

	bool GetIsDiamondBlock() const
	{
		return m_IsDiamondBlock;
	}

	bool GetShouldBreakOnSpot() const
	{
		return m_ShouldBreakOnSpot;
	}
	void SetShouldBreakOnSpot(bool shouldBreakOnSpot)
	{
		m_ShouldBreakOnSpot = shouldBreakOnSpot;
	}
	bool GetVerticalIsBorder() const
	{
		return m_IsVerBorder;
	}
	void SetIsVerticalBorder(bool isBorder)
	{
		m_IsVerBorder = isBorder;
	}

	bool GetHorizontalIsBorder() const
	{
		return m_IsHorBorder;
	}
	void SetIsHorizontalBorder(bool isBorder)
	{
		m_IsHorBorder = isBorder;
	}
private:

	static std::unique_ptr<StaticBlockState> m_pStaticBlockState;
	static std::unique_ptr<BreakingBlockState> m_pBreakingBlockState;
	static std::unique_ptr<IsBlockBreaking> m_pIsBlockBreaking;
	static std::unique_ptr<IsBlockNotBreaking> m_pIsBlockNotBreaking;
	static std::unique_ptr<IsBlockFinishedFlickering> m_pIsBlockFinishedFlickering;
	static std::unique_ptr<FlickeringBlockState> m_pFlickeringBlockState;
	static std::unique_ptr<VibratingState> m_pVibratingBorderState;
	static std::unique_ptr<StopVibrating> m_pStopVibratingBorderState;
	static std::unique_ptr<HasFinishedVibrating> m_pHasFinishedVibrating;
	static std::unique_ptr<IsVibrating> m_pIsVibrating;;
	
	glm::vec3 m_Position;
	glm::vec3 m_ColliderPosition;
	float m_PushSpeed;

	glm::vec3 m_Direction;

	int m_BlockIndex;
	bool m_Pushed{};
	bool m_IsBreakable;
	bool m_ContainsEggs;
	bool m_IsDiamondBlock;
	bool m_ShouldBreakOnSpot;
	bool m_IsHorBorder;
	bool m_IsVerBorder;
};

