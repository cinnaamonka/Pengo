#pragma once
#include <BaseComponent.h>
#include <Helpers.h>

class CollisionComponent final : public GameEngine::BaseComponent
{
public:

	CollisionComponent(GameEngine::GameObject* pGameObject);
	~CollisionComponent() = default;

	CollisionComponent(const CollisionComponent& other) = delete;
	CollisionComponent(CollisionComponent&& other) = delete;
	CollisionComponent& operator=(const CollisionComponent& other) = delete;
	CollisionComponent& operator=(CollisionComponent&& other) = delete;

	void HandleCollision(GameEngine::GameObject* actor, GameEngine::GameObject* border,glm::vec3& pushDirection,
		GameEngine::GameObject* pushedBlock, GameEngine::HitInfo& hitInfo,bool wasPushed);
	void HandleBlocksCollision(GameEngine::GameObject* gameObject);

	bool m_Pushed;


	bool GetHasCollided() const
	{
		return m_HasCollided;
	}
	enum class CollisionEvent
	{
		CollidedHor,
		CollidedVer,
		none
	};

	CollisionEvent m_CollisionEvent = CollisionEvent::none;
private:

	bool m_HasCollided;

};

