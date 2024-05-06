#pragma once
#include <memory>
#include <GameObject.h>
#include <BaseComponent.h>
#include <Helpers.h>
#include <BoxColliderComponent.h>
#include "BlocksStatesAndTransitions.h"
#include <Scene.h>

#include "HitObserver.h"
#include "CollisionComponent.h"

class BoxCollider;
class HitObserver;

class BaseBlock final : public GameEngine::BaseComponent
{
public:
	BaseBlock(GameEngine::GameObject* GOptr, int index, bool isBreakable, bool containsEggs);
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
		bool isBreakable = true, bool containsEggs = false,int clipAmount = 1,int blockSizeX = 20, int blockSizeY = 20,
		const glm::vec3& colliderBlockPos = glm::vec3{ 0,0,0 });

	int GetBlockIndex() const
	{
		
		return m_BlockIndex;
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
		if (!this) return false;

		return m_IsBreakable;
	}

	bool GetContainsEggs() const
	{
		if (!this) return false;

		return m_ContainsEggs;
	}
private:

	static std::unique_ptr<StaticBlockState> m_pStaticBlockState;
	static std::unique_ptr<BreakingBlockState> m_pBreakingBlockState;
	static std::unique_ptr<IsBlockBreaking> m_pIsBlockBreaking;
	static std::unique_ptr<IsBlockNotBreaking> m_pIsBlockNotBreaking;
	static std::unique_ptr<IsBlockFinishedFlickering> m_pIsBlockFinishedFlickering;
	static std::unique_ptr<FlickeringBlockState> m_pFlickeringBlockState;
	
	glm::vec3 m_Position;
	glm::vec3 m_ColliderPosition;
	float m_PushSpeed;

	glm::vec3 m_Direction;

	int m_BlockIndex;
	bool m_Pushed{};
	bool m_IsBreakable;
	bool m_ContainsEggs;

};

