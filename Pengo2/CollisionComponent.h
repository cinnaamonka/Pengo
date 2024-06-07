#pragma once
#include <BaseComponent.h>
#include <Helpers.h>
#include "BaseBlock.h"

class BaseBlock;

class CollisionComponent final : public GameEngine::BaseComponent
{
public:

	CollisionComponent(GameEngine::GameObject* pGameObject);
	~CollisionComponent() = default;

	CollisionComponent(const CollisionComponent& other) = delete;
	CollisionComponent(CollisionComponent&& other) = delete;
	CollisionComponent& operator=(const CollisionComponent& other) = delete;
	CollisionComponent& operator=(CollisionComponent&& other) = delete;

	bool IsColliding(GameEngine::GameObject* actor, GameEngine::HitInfo& hitInfo);
	bool IsBlockNearbyHorizontally(GameEngine::GameObject* actor, GameEngine::HitInfo& hitInfo);
	bool IsBlockNearbyVertically(GameEngine::GameObject* actor, GameEngine::HitInfo& hitInfo);
};

