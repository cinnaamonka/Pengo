#pragma once
#include <vector>
#include "EnemyActor.h"
#include <Subject.h>
#include <Scene.h>
#include <IObserver.h>
#include <AnimationComponent.h>
#include "EnvironmentObserver.h"
#include "ScoreObserver.h"
#include <ActorComponent.h>
#include <HUD.h>
#include <Scene.h>

class EnemyManager final
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
		 if constexpr (std::is_same_v<T, GameEngine::EnemyInfo>)
		{
			m_EnemyDirectionChanged.Attach(pObserver);
		}
	}

	template<typename T>
	void CreateMessage(T info)
	{
		
		 if constexpr (std::is_same_v<T, GameEngine::EnemyInfo>)
		{
			m_EnemyDirectionChanged.CreateMessage(info);
		}
		
	}

	void SetKilledEnemyIndex(int index) { m_KilledEnemyIndex = index; }
	int GetKilledEnemyIndex() const { return m_KilledEnemyIndex; }

	std::vector<GameEngine::GameObject*> GetEnemies() const { return m_EnemiesRef; }

	void CheckEnemiesCollision(std::vector<GameEngine::GameObject*>& blocks,
		int& m_PushBlockIndex, GameEngine::Subject<EventInfo>* eventSubject,GameEngine::Subject<Score>* scoreSubject,
		GameEngine::Subject<GameEngine::HUDEvent>* hudSubject);

	void HandleBorderCollision(GameEngine::GameObject*, GameEngine::Subject<EventInfo>* eventSubject);

	void CheckCollisionWithPushedBlock(GameEngine::GameObject* blocks);

	void CheckCollisionWithPlayer(std::vector<GameEngine::GameObject*> actors, GameEngine::Subject<GameEngine::HUDEvent>* hudSubject);
	void SpawnEnemy(const glm::vec3& pos);

	void CheckEnemiesCollectionSize(GameEngine::Subject<GameEngine::HUDEvent>* hudSubject);

	void AddPlayer(GameEngine::GameObject* actor);

	static EnemyPatrolState enemyPatrolState;
	static EnemyDyingState enemyDyingState;

	void SetPlayerEnemy(GameEngine::GameObject* playerEnemy) { m_pPlayerEnemy = playerEnemy; }
	GameEngine::GameObject* GetPlayerEnemy() const { return m_pPlayerEnemy; } 

private:

	void HandleMovement(GameEngine::HitInfo& hitInfo, std::vector<GameEngine::GameObject*> blocks,
		int currentBlockIndex, int currentEnemyIndex, const int randDirection, bool isHorizontal); 

	void KillEnemy(int index);
	void ResetEnemiesIndexes(); 


private:
	std::vector<GameEngine::GameObject*> m_EnemiesRef;
	GameEngine::Subject<GameEngine::EnemyInfo> m_EnemyDirectionChanged;

	GameEngine::GameObject* m_pPlayerEnemy;

	std::vector<glm::vec3> m_StartPositions;

	int m_KilledEnemyIndex;

	const int m_Radius = 20;

	GameEngine::Scene* m_pSceneRef;
	GameEngine::ActorComponent* m_pActorComponent;
};


