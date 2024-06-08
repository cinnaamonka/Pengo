#pragma once
#include <vector>
#include <Subject.h>
#include <BaseComponent.h>
#include "BaseBlock.h"
#include <IObserver.h>
#include "BlockObserver.h"
#include "EnemyManager.h"
#include <Scene.h>
#include <glm/glm.hpp>

class GameObject;

class Environment final : public GameEngine::BaseComponent
{
public:
	Environment(GameEngine::GameObject* pGameObject, std::vector<GameEngine::Block>& levelVertices, GameEngine::Scene* scene);
	~Environment() {};

	Environment(const Environment& other) = delete;
	Environment& operator=(const Environment& other) = delete;
	Environment(Environment&& other) noexcept = delete;
	Environment& operator=(Environment&& other) noexcept = delete;

	void CheckCollision();
	void CheckBlocksCollision(GameEngine::GameObject* pGameObject);
	void CheckEnemiesCollision(); 

	void Update() override;
	

	void SetActor(GameEngine::GameObject* pActor);
	void SetPlayerEnemy(GameEngine::GameObject* pPlayerEnemy)
	{
		m_pPlayerEnemy = pPlayerEnemy;
	}
	
	void SetEnemyManager(EnemyManager* pEnemyManager)
	{
		m_pEnemyManager = pEnemyManager;
	}
	template<typename T>
	void AttachObserver(GameEngine::IObserver<T>* pObserver)
	{
		if constexpr (std::is_same_v<T, GameEngine::HitInfo>)
		{
			m_CollisionHitInfoChanged.Attach(pObserver);
		}
		else if constexpr (std::is_same_v<T, glm::vec3>)
		{
			m_EggSpawnEvent.Attach(pObserver);
		}
		else if constexpr (std::is_same_v<T, EventInfo>)
		{
			m_EnvEvent.Attach(pObserver);
		}
		else if constexpr (std::is_same_v<T, Score>) 
		{
			m_ScoreAppearingEvent.Attach(pObserver); 
		}
		else if constexpr (std::is_same_v<T, GameEngine::HUDEvent>)
		{
			m_AddingScoreInHUDEvent.Attach(pObserver);
		}
	}

	void PushBlock(GameEngine::GameObject* actor);

	void CreateBlocksCollection(std::vector<GameEngine::Block> blocks, const std::string& name, const std::string& tag,
		int& offset, GameEngine::Scene* scene,BlocksTypes types,int clipTextureAmount = 1);

	void ResetBlocksIndexes();
	void DeleteBlockFromGame(const int blockIndex);
	void CheckDiamondBlocksPositions();
	void SpawnEnemyFromEggBlock();
	void SetBordersUntouched();
	void SetEnemyStunned(const int enemyIndex); 
	void EnemyPlayerBreakBlock();
private:

	void StopBlock(GameEngine::GameObject* block, GameEngine::HitInfo hitInfo);
	void BreakBlock(int index);  
	
	void CreateBorder(GameEngine::Scene* scene, bool isVertical, BlocksTypes type);
	void CheckBorderCollision(const GameEngine::HitInfo& hitInfo);
	
private:
	std::vector<GameEngine::GameObject*> m_pBlocks;

	std::vector<GameEngine::Block> m_LevelVertices;

	std::vector<GameEngine::GameObject*> m_pPlayers;
	GameEngine::GameObject* m_pPlayerEnemy;
	GameEngine::GameObject* m_pBorderBlock;
	EnemyManager* m_pEnemyManager;

	GameEngine::Subject<GameEngine::HitInfo> m_CollisionHitInfoChanged;
	GameEngine::Subject<BlockCollisionInfo> m_BlockCollisionInfo;
	GameEngine::Subject<glm::vec3> m_EggSpawnEvent;
	GameEngine::Subject<EventInfo> m_EnvEvent; 
	GameEngine::Subject<Score> m_ScoreAppearingEvent;
	GameEngine::Subject<GameEngine::HUDEvent> m_AddingScoreInHUDEvent;

	int m_PushBlockIndex = -1;

	const int m_BorderWidth;
	const int m_BorderLength;
	const int m_BorderHeight;
	const int m_ClipAmount = 16;

	std::unordered_map<int,glm::vec3> m_DiamondBlocksPositions;
	std::vector<int> m_EggBlocksIndexes;
	std::vector<GameEngine::GameObject*> m_pBorderBlocks;
};

