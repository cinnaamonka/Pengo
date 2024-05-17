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
#include <AnimationComponent.h>
#include "EnvironmentObserver.h"
#include "ScoreObserver.h"
#include <HUD.h>

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
		
	}

	void CheckEnemiesCollision(std::vector<GameEngine::GameObject*>& blocks,
		int& m_PushBlockIndex, GameEngine::Subject<EventInfo>* eventSubject,GameEngine::Subject<Score>* scoreSubject,
		GameEngine::Subject<GameEngine::HUDEvent>* hudSubject);

	void HandleBorderCollision(GameEngine::GameObject*);

	void CheckCollisionWithPushedBlock(GameEngine::GameObject* blocks);

	void CheckCollisionWithPlayer(const glm::vec3& pos, GameEngine::Subject<GameEngine::HUDEvent>* hudSubject);
private:

	void HandleMovement(GameEngine::HitInfo& hitInfo, std::vector<GameEngine::GameObject*> blocks,
		int currentBlockIndex, int currentEnemyIndex, const int randDirection, bool isHorizontal); 

	void KillEnemy(int index);
	void ResetEnemiesIndexes(); 


private:
	std::vector<GameEngine::GameObject*> m_EnemiesRef;
	GameEngine::Subject<GameEngine::HitInfo> m_EnemiesCollisionHitInfoChanged;
	GameEngine::Subject<GameEngine::EnemyInfo> m_EnemyDirectionChanged;

	std::vector<glm::vec3> m_StartPositions;

	int m_KilledEnemyIndex;

	static EnemyPatrolState enemyPatrolState;
	static EnemyDyingState enemyDyingState;

	const int m_Radius = 20;
};

