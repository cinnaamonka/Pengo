#include "InputCommands.h"
#include "GameObjectCommand.h"
#include "BaseCommand.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "TransformComponent.h"
#include "ActorComponent.h"
#include "FSM.h"

namespace GameEngine
{
	MoveCommand::MoveCommand(GameObject* gameObject, glm::vec3 direction)
		: GameObjectCommand(gameObject),
		m_Direction(glm::normalize(direction))
	{
		
	}

	void GameEngine::MoveCommand::Execute()
	{
		glm::vec3 currentLocalPosition = GetGameObject()->GetComponent<TransformComponent>()->GetLocalPosition();
		currentLocalPosition += m_Direction * GetGameObject()->GetComponent<ActorComponent>()->GetSpeed() * TimeManager::GetElapsed();
		GetGameObject()->GetComponent<TransformComponent>()->SetLocalPosition(currentLocalPosition);
		GetGameObject()->GetComponent<ActorComponent>()->SetCollisionCanBeChecked(true);
		GetGameObject()->GetComponent<AnimationComponent>()->SetWasInputGiven(true);
		GetGameObject()->GetComponent<AnimationComponent>()->SetMovementDirection(m_Direction);
	}

	StopCollisionCheck::StopCollisionCheck(GameObject* pGameObject)
		: GameObjectCommand(pGameObject)
	{
	}
	void GameEngine::StopCollisionCheck::Execute()
	{
		GetGameObject()->GetComponent<ActorComponent>()->SetCollisionCanBeChecked(false);

	}

	PushCommand::PushCommand(GameObject* gameObject):
		GameObjectCommand(gameObject)
	{

	}
	void PushCommand::Execute()
	{
		GetGameObject()->GetComponent<AnimationComponent>()->SetWasPushed(true);
		GetGameObject()->GetComponent<ActorComponent>()->SetCollisionCanBeChecked(true);

	}
}
