#include "EnemyManager.h"

EnemyManager::EnemyManager(int enemiesAmount)
{
	for (int i = 0; i < enemiesAmount; ++i)
	{
		auto enemyActor = std::make_unique<EnemyActor>(); 

		m_Enemies.push_back(std::move(enemyActor));
	}
}
