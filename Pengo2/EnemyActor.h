#pragma once

#include <memory>
#include <GameObject.h>
#include <Helpers.h>
#include <StatesAndTransitions.h>
#include "StatesAndTransitionsAI.h"

class EnemyActor final
{
public:
	EnemyActor();
	~EnemyActor() = default;

	EnemyActor(const EnemyActor& other) = delete;
	EnemyActor& operator=(const EnemyActor& other) = delete;
	EnemyActor(EnemyActor&& other) noexcept = delete;
	EnemyActor& operator=(EnemyActor&& other) noexcept = delete;

	static std::unique_ptr<GameEngine::GameObject> CreateEnemy();

private:
	GameEngine::GameObject* m_pEnemy;

	int m_HorizontalAmountOfFrames = 8;
	int m_VerticalAmountOfFrames = 5;

	static std::unique_ptr<GameEngine::MovingState> m_RunningState; 
	static std::unique_ptr<GameEngine::AttackState> m_PushingState; 

	static std::unique_ptr<PatrolState> m_MovingState;
	static std::unique_ptr<ChaseState> m_ChaseState;
	static std::unique_ptr<HasNoticedActor> m_HasNoticedActor;

	static std::unique_ptr<GameEngine::HasAttacked> m_IsPengoAttacked;
	static std::unique_ptr<GameEngine::HasNotAttacked> m_IsPengoNotAttacked;
};

