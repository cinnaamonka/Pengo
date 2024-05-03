#pragma once
#include <vector>
#include <memory>
#include "EnemyActor.h"

class EnemyManager
{

public:
	EnemyManager(int enemiesAmount);
	~EnemyManager() = default;
	EnemyManager(const EnemyManager& other) = delete;
	EnemyManager(EnemyManager&& other) = delete;
	EnemyManager& operator=(const EnemyManager& other) = delete;
	EnemyManager& operator=(EnemyManager&& other) = delete;

	const size_t GetEnemiesAmount() const
	{
		return m_Enemies.size();
	}
	
	std::vector<std::unique_ptr<EnemyActor>>& GetEnemies()
	{
		return m_Enemies;
	}

private:
	std::vector<std::unique_ptr<EnemyActor>> m_Enemies;
};

