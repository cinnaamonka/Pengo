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
		GetGameObject()->GetComponent<FSM>()->GetBlackboard()->ChangeData("WasInputGiven", true);
		GetGameObject()->GetComponent<FSM>()->GetBlackboard()->ChangeData("MovementDirection", m_Direction);
	}

	ScoreCommand::ScoreCommand(GameObject* pGameObject, int amount)
		: GameObjectCommand(pGameObject)
		, m_Amount(amount)
	{
	}
	void GameEngine::ScoreCommand::Execute()
	{
		auto pScoreComponent = GetGameObject()->GetComponent<GameEngine::ActorComponent>();
		if (pScoreComponent) pScoreComponent->AddScore(m_Amount);

	}

	LifesCommand::LifesCommand(GameObject* pGameObject,int lifesAmount)
		:GameObjectCommand(pGameObject),
		m_LifesAmount(lifesAmount)

	{

	}
	void LifesCommand::Execute()
	{
		auto pLivesComponent = GetGameObject()->GetComponent<GameEngine::ActorComponent>();
		if (pLivesComponent) pLivesComponent->Damage(m_LifesAmount);
	}
	PushCommand::PushCommand(GameObject* gameObject):
		GameObjectCommand(gameObject)
	{

	}
	void PushCommand::Execute()
	{
		GetGameObject()->GetComponent<FSM>()->GetBlackboard()->ChangeData("WasBlockPushed", true);
		GetGameObject()->GetComponent<ActorComponent>()->SetCollisionCanBeChecked(true);

	}
}
