#pragma once
#include <Helpers.h>
#include <BlackboardComponent.h>

class BreakingEggState : public GameEngine::FSMState
{
public:
	BreakingEggState() = default;
	~BreakingEggState() = default;

	virtual void OnEnter(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void Update(GameEngine::BlackboardComponent* pBlackboard) override;

};
class BrokenEggState : public GameEngine::FSMState
{
public:
	BrokenEggState() = default;
	~BrokenEggState() = default;

	virtual void OnEnter(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::BlackboardComponent*) override {};
	virtual void Update(GameEngine::BlackboardComponent*) override {};

};
class WaitingState : public GameEngine::FSMState
{
public:
	WaitingState() = default;
	~WaitingState() = default;

	virtual void OnEnter(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::BlackboardComponent*) override {};
	virtual void Update(GameEngine::BlackboardComponent* pBlackboard) override;

};
class IsEggBroken : public GameEngine::FSMCondition
{
public:
	IsEggBroken() = default;
	~IsEggBroken() = default;

	virtual bool Evaluate(GameEngine::BlackboardComponent* pBlackboard) const override;
};
class IsWaiting : public GameEngine::FSMCondition
{
public:
	IsWaiting() = default;
	~IsWaiting() = default;

	virtual bool Evaluate(GameEngine::BlackboardComponent* pBlackboard) const override;
};
