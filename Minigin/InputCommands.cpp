#include "InputCommands.h"
#include "GameObjectCommand.h"
#include "BaseCommand.h"
#include "GameObject.h"
#include "Time2.h"
#include "TransformComponent.h"
#include "ActorComponent.h"


namespace GameEngine
{
	MoveCommand::MoveCommand(GameObject* gameObject, glm::vec3 direction, float speed)
		: GameObjectCommand(gameObject),
		m_Direction(glm::normalize(direction)),
		m_Speed(speed)
	{
	}

	void GameEngine::MoveCommand::Execute()
	{
		glm::vec3 currentLocalPosition = GetGameObject()->GetComponent<TransformComponent>()->GetLocalPosition();
		currentLocalPosition += m_Direction * m_Speed * Time::GetElapsed();
		GetGameObject()->GetComponent<TransformComponent>()->SetLocalPosition(currentLocalPosition);
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
}
