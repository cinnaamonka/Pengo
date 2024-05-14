#include "EnemyDirectionObserver.h"
#include <AnimationComponent.h>
#include "EnemyActor.h"

EnemyDirectionObserver::EnemyDirectionObserver(GameEngine::GameObject* pGameObject, int index):
	BaseComponent(pGameObject),
	m_Index(index)
{

}

void EnemyDirectionObserver::Notify(const GameEngine::EnemyInfo& info)
{
	if (info.index != m_Index) return;
	
	glm::vec3 previousDirection = GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->GetMovementDirection();

	if (previousDirection != info.position && !GetGameObject()->GetComponent<EnemyActor>()->GetIsKilled())
	{
		GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->SetMovementDirection(info.position);
	}
}
