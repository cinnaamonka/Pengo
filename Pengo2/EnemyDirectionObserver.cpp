#include "EnemyDirectionObserver.h"

#include "EnemyActor.h"

EnemyDirectionObserver::EnemyDirectionObserver(GameEngine::GameObject* pGameObject, int index):
	BaseComponent(pGameObject),
	m_Index(index)
{
	m_pAnimationComponent = GetGameObject()->GetComponent<GameEngine::AnimationComponent>();
}

void EnemyDirectionObserver::Notify(const GameEngine::EnemyInfo& info)
{
	if (info.index != m_Index) return;
	
	glm::vec3 previousDirection = m_pAnimationComponent->GetMovementDirection();

	if (previousDirection != info.position && !GetGameObject()->GetComponent<EnemyActor>()->GetIsKilled())
	{
		m_pAnimationComponent->SetMovementDirection(info.position);
	}
}
