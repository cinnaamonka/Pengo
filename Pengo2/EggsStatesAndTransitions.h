#pragma once
#include <Helpers.h>
#include <AnimationComponent.h>
#include <BlackboardComponent.h>

class BreakingEggState : public GameEngine::FSMState
{
public:
	BreakingEggState() = default;
	~BreakingEggState() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void Update(GameEngine::AnimationComponent* pBlackboard) override;

};
class BrokenEggState : public GameEngine::FSMState
{
public:
	BrokenEggState() = default;
	~BrokenEggState() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::AnimationComponent*) override {};
	virtual void Update(GameEngine::AnimationComponent*) override {};

};
class WaitingState : public GameEngine::FSMState
{
public:
	WaitingState() = default;
	~WaitingState() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::AnimationComponent*) override {};
	virtual void Update(GameEngine::AnimationComponent* pBlackboard) override;

};
class IsEggBroken : public GameEngine::FSMCondition
{
public:
	IsEggBroken() = default;
	~IsEggBroken() = default;

	virtual bool Evaluate(GameEngine::AnimationComponent* pBlackboard) const override;
};
class IsWaiting : public GameEngine::FSMCondition
{
public:
	IsWaiting() = default;
	~IsWaiting() = default;

	virtual bool Evaluate(GameEngine::AnimationComponent* pBlackboard) const override;
};
