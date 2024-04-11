#pragma once
#include "BaseComponent.h"
#include "IObserver.h"
#include <Helpers.h>

class GameObject;

class CollisionObserver : public GameEngine::BaseComponent, public GameEngine::IObserver<GameEngine::CollisionState>
{
public:

	CollisionObserver(GameEngine::GameObject* pGameObject);
	~CollisionObserver() = default;
	CollisionObserver(const CollisionObserver& other) = delete;
	CollisionObserver& operator=(const CollisionObserver& other) = delete;
	CollisionObserver(CollisionObserver&& other) = delete;

	void Notify(const GameEngine::CollisionState& message_from_subject) override; 
};

