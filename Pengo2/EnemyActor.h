#pragma once

#include <memory>

#include <Helpers.h>
#include <BaseComponent.h>
#include <GameObject.h>
#include <Subject.h>
#include <IObserver.h>
#include "AIStatesAndTransitions.h"
#include "EnemyStatesAndTransitions.h"

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

	template<typename T>
	void AttachObserver(GameEngine::IObserver<T>* pObserver)
	{
		if constexpr (std::is_same_v<T, bool>)
		{
			m_ActorKilled.Attach(pObserver);
		}
	}

	void SetActor(GameEngine::GameObject* pActor) { m_pPlayer = pActor; }

	GameEngine::GameObject* GetPlayer() const { return m_pPlayer; }


	void KillPlayer(); 
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

	GameEngine::Subject<bool> m_ActorKilled;

	GameEngine::GameObject* m_pPlayer;
};

