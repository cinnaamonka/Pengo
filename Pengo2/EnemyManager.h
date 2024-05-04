#pragma once
#include <vector>
#include <memory>
#include "EnemyActor.h"
#include <Subject.h>
#include <Helpers.h>
#include <IObserver.h>

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
		return m_pEnemies.size();
	}
	
	std::vector<std::unique_ptr<GameEngine::GameObject>>& GetEnemies()
	{
		return m_pEnemies;
	}

	template<typename T>
	void AttachObserver(GameEngine::IObserver<T>* pObserver)
	{
		if constexpr (std::is_same_v<T, GameEngine::HitInfo>)
		{
			m_EnemiesCollisionHitInfoChanged.Attach(pObserver);
		}
		else if constexpr (std::is_same_v<T, glm::vec3>)
		{
			m_EnemyDirectionChanged.Attach(pObserver); 
		}
	}

	template<typename T>
	void CreateMessage(T info)
	{
		if constexpr (std::is_same_v<T, GameEngine::HitInfo>)
		{
			m_EnemiesCollisionHitInfoChanged.CreateMessage(info);
		}
		else if constexpr (std::is_same_v<T, glm::vec3>) 
		{
			m_EnemyDirectionChanged.CreateMessage(info);
		}
	
		
	}

	bool CheckEnemiesCollision( GameEngine::HitInfo& hitInfo, int enemyIndex, int currentBlockIndex,
		 std::vector<GameEngine::GameObject*> blocks);

private:
	std::vector<std::unique_ptr<GameEngine::GameObject>> m_pEnemies;
	std::vector<GameEngine::GameObject*> m_EnemiesRef;
	GameEngine::Subject<GameEngine::HitInfo> m_EnemiesCollisionHitInfoChanged;
	GameEngine::Subject<glm::vec3> m_EnemyDirectionChanged;
};

