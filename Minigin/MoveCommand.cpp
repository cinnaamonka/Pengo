#include "MoveCommand.h"
#include "GameObjectCommand.h"
#include "BaseCommand.h"
#include "GameObject.h"
#include "Time.h"
#include "TransformComponent.h"

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
}
