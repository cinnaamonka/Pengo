#pragma once
#include <Helpers.h>
#include <BlackboardComponent.h>

class PatrolState : public GameEngine::FSMState
{
public:
	PatrolState() = default;
	~PatrolState() = default;

	virtual void OnEnter(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::BlackboardComponent* pBlackboard) override; 
	virtual void Update(GameEngine::BlackboardComponent* pBlackboard) override;
};

class ChaseState : public GameEngine::FSMState
{
public:
	ChaseState() = default;
	~ChaseState() = default;

	virtual void OnEnter(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void Update(GameEngine::BlackboardComponent* pBlackboard) override;
};

class HasNoticedActor : public GameEngine::FSMCondition
{
public:
	HasNoticedActor() = default;
	~HasNoticedActor() = default;

	virtual bool Evaluate(GameEngine::BlackboardComponent* pBlackboard) const override;
};