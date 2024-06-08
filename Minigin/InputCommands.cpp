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
		m_pTransformComponent = GetGameObject()->GetComponent<GameEngine::TransformComponent>();
		m_pActorComponent = GetGameObject()->GetComponent<GameEngine::ActorComponent>();
		m_pAnimationComponent = GetGameObject()->GetComponent<GameEngine::AnimationComponent>();
	}

	void GameEngine::MoveCommand::Execute()
	{
		if (GetGameObject()->IsDestroyed()) return;

		glm::vec3 currentLocalPosition = m_pTransformComponent->GetLocalPosition();
		currentLocalPosition += m_Direction * m_pActorComponent->GetSpeed() * TimeManager::GetElapsed();
		m_pTransformComponent->SetLocalPosition(currentLocalPosition);
		m_pActorComponent->SetCollisionCanBeChecked(true);
		m_pAnimationComponent->SetWasInputGiven(true);
		m_pAnimationComponent->SetMovementDirection(m_Direction);
	}

	StopCollisionCheck::StopCollisionCheck(GameObject* pGameObject)
		: GameObjectCommand(pGameObject)
	{
		m_pActorComponent = GetGameObject()->GetComponent<ActorComponent>();
	}
	void GameEngine::StopCollisionCheck::Execute()
	{
		if (GetGameObject()->IsDestroyed()) return;

		m_pActorComponent->SetCollisionCanBeChecked(false);

	}

	PushCommand::PushCommand(GameObject* gameObject):
		GameObjectCommand(gameObject)
	{
		m_pActorComponent = GetGameObject()->GetComponent<ActorComponent>();
		m_pAnimationComponent = GetGameObject()->GetComponent<AnimationComponent>();
	}
	void PushCommand::Execute()
	{
		if (GetGameObject()->IsDestroyed()) return;
		m_pAnimationComponent->SetWasPushed(true);
		m_pActorComponent->SetCollisionCanBeChecked(true);

	}
}
