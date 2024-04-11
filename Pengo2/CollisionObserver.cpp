#pragma once
#include "CollisionObserver.h"
#include <ActorComponent.h>


CollisionObserver::CollisionObserver(GameEngine::GameObject* pGameObject) :
	BaseComponent(pGameObject)
{
}

void CollisionObserver::Notify(const GameEngine::CollisionState& message_from_subject)
{
	switch (message_from_subject)
	{
	case GameEngine::CollisionState::Colliding:
		GetGameObject()->GetComponent<GameEngine::ActorComponent>()->SetSpeed(0);
		break;

	case GameEngine::CollisionState::NotColliding:
		GetGameObject()->GetComponent<GameEngine::ActorComponent>()->SetSpeed(30.0f);
		break;
	}

}



