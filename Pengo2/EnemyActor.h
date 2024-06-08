#pragma once

#include <memory>

#include <Helpers.h>
#include <BaseComponent.h>
#include <GameObject.h>
#include <Subject.h>
#include <IObserver.h>
#include "AIStatesAndTransitions.h"
#include "EnemyAnimationStates.h"

class EnemyActor final :public GameEngine::BaseComponent
{
public:
	EnemyActor(GameEngine::GameObject* pGameObject);
	~EnemyActor() = default;

	EnemyActor(const EnemyActor& other) = delete;
	EnemyActor& operator=(const EnemyActor& other) = delete;
	EnemyActor(EnemyActor&& other) noexcept = delete;
	EnemyActor& operator=(EnemyActor&& other) noexcept = delete;

	static std::unique_ptr<GameEngine::GameObject> CreateEnemy(const glm::vec3& pos, int index);

	void SetHasKilledActor(bool hasKilledActor) { m_HasKilledActor = hasKilledActor; }
	bool GetHasKilledActor() const { return m_HasKilledActor; }

	void SetActor(GameEngine::GameObject* pActor) 
	{
		m_pPlayers.push_back(pActor); 
	}

	std::vector<GameEngine::GameObject*> GetPlayer() const { return m_pPlayers; }

	void KillPlayer(int killedPlayerIndex);

	void Update()override;
	void HandleInput(IEnemyAnimationState* state); 

	bool GetIsKilled() const
	{
 	return m_IsKilled;
	}

	void SetIsKilled(bool isKilled)
	{
		m_IsKilled = isKilled;
	}

	static std::unique_ptr<PatrolState> m_MovingState;
	static std::unique_ptr<ChaseState> m_ChaseState;
	static std::unique_ptr<HasNoticedActor> m_HasNoticedActor;

private:

	const int m_HorizontalAmountOfFrames = 8;
	const int m_VerticalAmountOfFrames = 5;

	bool m_HasKilledActor;

	std::vector<GameEngine::GameObject*> m_pPlayers;

	IEnemyAnimationState* m_AnimationState;
	bool m_IsKilled;

};

