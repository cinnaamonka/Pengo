#include "InputCommands.h"
#include "GameObjectCommand.h"
#include "BaseCommand.h"
#include "GameObject.h"
#include "Time.h"
#include "TransformComponent.h"
#include "ScoreComponent.h"


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
		, m_Amount{ amount }
	{
	}
	void GameEngine::ScoreCommand::Execute()
	{
		auto pLives = GetGameObject()->GetComponent<GameEngine::ScoreComponent>();
		if (pLives) pLives->AddScore(m_Amount);

	}
}
