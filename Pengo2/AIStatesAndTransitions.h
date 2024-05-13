#pragma once
#include <Helpers.h>
#include <FSM.h>

class PatrolState : public GameEngine::FSMState
{
public:
	PatrolState() = default;
	~PatrolState() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void Update(GameEngine::AnimationComponent* pBlackboard) override;
};

class ChaseState : public GameEngine::FSMState
{
public:
	ChaseState() = default;
	~ChaseState() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void Update(GameEngine::AnimationComponent* pBlackboard) override;
};

class HasNoticedActor : public GameEngine::FSMCondition
{
public:
	HasNoticedActor() = default;
	~HasNoticedActor() = default;

	virtual bool Evaluate(GameEngine::AnimationComponent* pBlackboard) const override;
};