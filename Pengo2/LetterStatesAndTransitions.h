#pragma once
#include <Helpers.h>
#include <AnimationComponent.h>
#include <FSM.h>

class StaticLetterState : public GameEngine::FSMState 
{
public:
	StaticLetterState() = default;
	~StaticLetterState() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pAnimationComponent) override;
	virtual void OnExit(GameEngine::AnimationComponent*) override {};
	virtual void Update(GameEngine::AnimationComponent*) override;
private:
	const int m_NumberOfEnterStateFrames = 1;
	const int m_HorizontalOffset = 0;
	const int m_VerticalOffset = 1;
	const int m_FramesPerSec = 1;
	const int m_MaxAnimationTimesAmount = 50;
};
class FlyckeringLetterState : public GameEngine::FSMState
{
public:
	FlyckeringLetterState() = default;
	~FlyckeringLetterState() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pAnimationComponent) override;
	virtual void OnExit(GameEngine::AnimationComponent*) override;
	virtual void Update(GameEngine::AnimationComponent* pAnimationComponent) override;

private:
	const int m_NumberOfEnterStateFrames = 1;
	const int m_HorizontalOffset = 0;
	const int m_VerticalOffset = 1;
	const int m_FramesPerSec = 1;
	const int m_MaxAnimationTimesAmount = 50;
};

class ShouldStartFlyckering : public GameEngine::FSMCondition
{
public:
	ShouldStartFlyckering() = default;
	~ShouldStartFlyckering() = default;

	virtual bool Evaluate(GameEngine::AnimationComponent* pAnimationComponent) const override;
};
class ShouldStopFlyckering : public GameEngine::FSMCondition
{
public:
	ShouldStopFlyckering() = default;
	~ShouldStopFlyckering() = default;

	virtual bool Evaluate(GameEngine::AnimationComponent* pAnimationComponent) const override;
};