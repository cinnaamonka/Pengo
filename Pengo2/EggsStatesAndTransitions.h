#pragma once
#include <AnimationComponent.h>
#include <FSM.h>

class BreakingEggState final : public GameEngine::FSMState
{
public:
	BreakingEggState() = default;
	~BreakingEggState() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::AnimationComponent*) override {};
	virtual void Update(GameEngine::AnimationComponent* pBlackboard) override;
private:
	const int m_NumberOfEnterStateFrames = 3;
	const int m_FramesPerSec = 1;
	const int m_HorizontalOffset = 1;
	const int m_VerticalOffset = 0;
};
class BrokenEggState final : public GameEngine::FSMState
{
public:
	BrokenEggState() = default;
	~BrokenEggState() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::AnimationComponent*) override {};
	virtual void Update(GameEngine::AnimationComponent*) override {};

};
class WaitingState final : public GameEngine::FSMState
{
public:
	WaitingState() = default;
	~WaitingState() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::AnimationComponent*) override {};
	virtual void Update(GameEngine::AnimationComponent* pBlackboard) override;

private:
	const int m_NumberOfEnterStateFrames = 1;
	const int m_FramesPerSec = 1;
	const int m_HorizontalOffset = 0;
	const int m_VerticalOffset = 0;
};
class IsEggBroken final : public GameEngine::FSMCondition
{
public:
	IsEggBroken() = default;
	~IsEggBroken() = default;

	virtual bool Evaluate(GameEngine::AnimationComponent* pBlackboard) const override;
};
class IsWaiting final : public GameEngine::FSMCondition
{
public:
	IsWaiting() = default;
	~IsWaiting() = default;

	virtual bool Evaluate(GameEngine::AnimationComponent* pBlackboard) const override;
};
