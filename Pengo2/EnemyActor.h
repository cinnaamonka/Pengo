#pragma once
#include <memory>
#include <GameObject.h>
#include <Helpers.h>
#include <memory>
#include <StatesAndTransitions.h>

class EnemyActor final
{
public:
	EnemyActor();
	~EnemyActor() = default;

	EnemyActor(const EnemyActor& other) = delete;
	EnemyActor& operator=(const EnemyActor& other) = delete;
	EnemyActor(EnemyActor&& other) noexcept = delete;
	EnemyActor& operator=(EnemyActor&& other) noexcept = delete;

	std::unique_ptr<GameEngine::GameObject>& GetActorGameObject();

private:
	std::unique_ptr<GameEngine::GameObject> m_pEnemy;

	int m_HorizontalAmountOfFrames = 8;
	int m_VerticalAmountOfFrames = 5;

	std::unique_ptr<GameEngine::MovingState> m_RunningState; 
	std::unique_ptr<GameEngine::AttackState> m_PushingState; 

	std::unique_ptr<GameEngine::HasAttacked> m_IsPengoAttacked;
	std::unique_ptr<GameEngine::HasNotAttacked> m_IsPengoNotAttacked;
};

