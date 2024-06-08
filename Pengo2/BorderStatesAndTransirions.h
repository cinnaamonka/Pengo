#pragma once
#include <Helpers.h>
#include <FSM.h>

class VibratingState final : public GameEngine::FSMState
{
public:
	VibratingState() = default;
	~VibratingState() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::AnimationComponent*) override {};
	virtual void Update(GameEngine::AnimationComponent* pBlackboard) override;

private:
	const int m_NumberOfEnterStateFrames = 2;
	const int m_FramesPerSec = 10;
	const int m_HorizontalOffset = 0;
	const int m_VerticalOffset = 1;
};
class StopVibrating final : public GameEngine::FSMState
{
public:
	StopVibrating() = default;
	~StopVibrating() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::AnimationComponent*) override {};
	virtual void Update(GameEngine::AnimationComponent*) override {};

private:
	const int m_NumberOfEnterStateFrames = 1;
	const int m_FramesPerSec = 10;
	const int m_HorizontalOffset = 0;
	const int m_VerticalOffset = 0;
};

class HasFinishedVibrating final : public GameEngine::FSMCondition
{
public:
	HasFinishedVibrating() = default;
	~HasFinishedVibrating() = default;

	virtual bool Evaluate(GameEngine::AnimationComponent* pBlackboard) const override;
};
class IsVibrating final : public GameEngine::FSMCondition
{
public:
	IsVibrating() = default;
	~IsVibrating() = default;

	virtual bool Evaluate(GameEngine::AnimationComponent* pBlackboard) const override;
};

