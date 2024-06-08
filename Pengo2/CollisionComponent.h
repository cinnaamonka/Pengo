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

	bool IsColliding(GameEngine::GameObject* actor, GameEngine::HitInfo& hitInfo) const;
	bool IsBlockNearbyHorizontally(GameEngine::GameObject* actor, GameEngine::HitInfo& hitInfo) const;
	bool IsBlockNearbyVertically(GameEngine::GameObject* actor, GameEngine::HitInfo& hitInfo)const;

	void HandleHitEvent(const GameEngine::HitInfo& hitInfo); 

private:
	void ResetHorizontalPosition(const GameEngine::Rect& actorShape, const GameEngine::HitInfo& hitInfo);
	void ResetVerticalPosition(const GameEngine::Rect& actorShape, const GameEngine::HitInfo& hitInfo);
private:
	const float m_TopOffset = 0.9f;
	const float m_BottomOffset = 0.1f;
};

