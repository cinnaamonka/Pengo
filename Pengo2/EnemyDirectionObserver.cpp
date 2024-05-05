#include "EnemyDirectionObserver.h"
#include <BlackboardComponent.h>

EnemyDirectionObserver::EnemyDirectionObserver(GameEngine::GameObject* pGameObject, int index):
	BaseComponent(pGameObject),
	m_Index(index)
{

}

void EnemyDirectionObserver::Notify(const GameEngine::EnemyInfo& info)
{
	if (info.index != m_Index) return;
	
	glm::vec3 previousDirection;
	GetGameObject()->GetComponent<GameEngine::BlackboardComponent>()->GetData("MovementDirection", previousDirection); 

	if (previousDirection != info.position)
	{
		GetGameObject()->GetComponent<GameEngine::BlackboardComponent>()->ChangeData("MovementDirection", info.position);
	}
}
