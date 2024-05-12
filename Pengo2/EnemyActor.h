#pragma once

#include <memory>

#include <Helpers.h>
#include <BaseComponent.h>
#include <GameObject.h>
#include <Subject.h>
#include <IObserver.h>
#include "AIStatesAndTransitions.h"
#include "EnemyStatesAndTransitions.h"
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

	static std::unique_ptr<GameEngine::GameObject> CreateEnemy(glm::vec3& pos, int index);

	void SetHasKilledActor(bool hasKilledActor) { m_HasKilledActor = hasKilledActor; }
	bool GetHasKilledActor() const { return m_HasKilledActor; }

	void SetActor(GameEngine::GameObject* pActor) { m_pPlayer = pActor; }

	GameEngine::GameObject* GetPlayer() const { return m_pPlayer; }


	void KillPlayer();

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
private:

	int m_HorizontalAmountOfFrames = 8;
	int m_VerticalAmountOfFrames = 5;

	bool m_HasKilledActor;

	static std::unique_ptr<MovingState> m_RunningState;
	static std::unique_ptr<AttackState> m_PushingState;
	static std::unique_ptr<PatrolState> m_MovingState;
	static std::unique_ptr<ChaseState> m_ChaseState;
	static std::unique_ptr<HasNoticedActor> m_HasNoticedActor;
	static std::unique_ptr<HasAttacked> m_IsPengoAttacked;
	static std::unique_ptr<HasNotAttacked> m_IsPengoNotAttacked;

	GameEngine::GameObject* m_pPlayer;

	IEnemyAnimationState* m_AnimationState;
	bool m_IsKilled;

};

