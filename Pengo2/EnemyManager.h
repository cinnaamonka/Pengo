#pragma once
#include <vector>
#include <memory>
#include "EnemyActor.h"
#include <Subject.h>
#include <Helpers.h>
#include <Scene.h>
#include <IObserver.h>
#include <Subject.h>
#include "BlockObserver.h"
#include "EnemyAnimationStates.h"

class EnemyManager
{

public:
	EnemyManager(int enemiesAmount, std::vector<glm::vec3>& positions, GameEngine::Scene* scene, GameEngine::GameObject* actor);
	~EnemyManager() = default;
	EnemyManager(const EnemyManager& other) = delete;
	EnemyManager(EnemyManager&& other) = delete;
	EnemyManager& operator=(const EnemyManager& other) = delete;
	EnemyManager& operator=(EnemyManager&& other) = delete;

	template<typename T>
	void AttachObserver(GameEngine::IObserver<T>* pObserver)
	{
		if constexpr (std::is_same_v<T, GameEngine::HitInfo>)
		{
			m_EnemiesCollisionHitInfoChanged.Attach(pObserver);
		}
		else if constexpr (std::is_same_v<T, GameEngine::EnemyInfo>)
		{
			m_EnemyDirectionChanged.Attach(pObserver);
		}
		else if constexpr (std::is_same_v<T, glm::vec3>)
		{
			m_PlayerPositionChanged.Attach(pObserver);
		}
	}

	template<typename T>
	void CreateMessage(T info)
	{
		if constexpr (std::is_same_v<T, GameEngine::HitInfo>)
		{
			m_EnemiesCollisionHitInfoChanged.CreateMessage(info);
		}
		else if constexpr (std::is_same_v<T, GameEngine::EnemyInfo>)
		{
			m_EnemyDirectionChanged.CreateMessage(info);
		}
		else if constexpr (std::is_same_v<T, glm::vec3>)
		{
			m_PlayerPositionChanged.CreateMessage(info);
		}


	}

	void CheckEnemiesCollision(std::vector<GameEngine::GameObject*> blocks, GameEngine::Subject<BlockCollisionInfo>* subject,int m_PushBlockIndex);

	void HandleBorderCollision(GameEngine::GameObject*);

	void CheckCollisionWithPushedBlock(GameEngine::GameObject* blocks);

private:

	void HandleMovement(GameEngine::HitInfo& hitInfo, std::vector<GameEngine::GameObject*> blocks,
		int currentBlockIndex, int currentEnemyIndex, const int randDirection, bool isHorizontal); 

	void KillEnemy(int index);


private:
	std::vector<GameEngine::GameObject*> m_EnemiesRef;
	GameEngine::Subject<GameEngine::HitInfo> m_EnemiesCollisionHitInfoChanged;
	GameEngine::Subject<GameEngine::EnemyInfo> m_EnemyDirectionChanged;
	GameEngine::Subject<glm::vec3> m_PlayerPositionChanged;
	
	std::vector<glm::vec3> m_StartPositions;

	int m_KilledEnemyIndex;

	static EnemyPatrolState enemyPatrolState;
	static EnemyDyingState enemyDyingState;
};

