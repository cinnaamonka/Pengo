#pragma once
#include <memory>
#include <GameObject.h>
#include <BaseComponent.h>
#include <Helpers.h>
#include <BoxColliderComponent.h>
#include <Scene.h>

#include "HitObserver.h"

class BoxCollider;
class HitObserver;

class BaseBlock final : public GameEngine::BaseComponent
{
public:
	BaseBlock(GameEngine::GameObject* GOptr);
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

	static std::unique_ptr<GameEngine::GameObject> CreateBlock(const glm::vec3& position, const std::string& filename,
		int blockSizeX = 20, int blockSizeY = 20, const glm::vec3& colliderBlockPos = glm::vec3{ 0,0,0 });

	enum class CollisionEvent
	{
		collidedHor,
		collidedVer,
		none,
		both
	};

	CollisionEvent m_CollisionEvent = CollisionEvent::none;

private:

	std::unique_ptr<GameEngine::GameObject> m_pGameObject;

	glm::vec3 m_Position;
	glm::vec3 m_ColliderPosition;
	float m_PushSpeed;

	glm::vec3 m_Direction;

	bool m_HasCollidedHor = false;

};

