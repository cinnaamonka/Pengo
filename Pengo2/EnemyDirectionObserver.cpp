#include "EnemyDirectionObserver.h"
#include <BlackboardComponent.h>

EnemyDirectionObserver::EnemyDirectionObserver(GameEngine::GameObject* pGameObject):
	BaseComponent(pGameObject)
{

}

void EnemyDirectionObserver::Notify(const glm::vec3& direction)
{
	glm::vec3 previousDirection;
	GetGameObject()->GetComponent<GameEngine::BlackboardComponent>()->GetData("MovementDirection", previousDirection); 

	if (previousDirection != direction)
	{
		GetGameObject()->GetComponent<GameEngine::BlackboardComponent>()->ChangeData("MovementDirection", direction);
	}
}
