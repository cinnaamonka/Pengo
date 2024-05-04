#include "EnemyManager.h"
#include "HitObserver.h"
#include "EnemyDirectionObserver.h"

EnemyManager::EnemyManager(int enemiesAmount)
{
	for (int i = 0; i < enemiesAmount; ++i)
	{
		auto enemyActor = EnemyActor::CreateEnemy(); 
		m_EnemiesCollisionHitInfoChanged.Attach(enemyActor->GetComponent<HitObserver>());
		m_EnemyDirectionChanged.Attach(enemyActor->GetComponent<EnemyDirectionObserver>());
		m_Enemies.push_back(std::move(enemyActor));
	}
}
