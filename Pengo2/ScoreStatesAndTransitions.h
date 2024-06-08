#pragma once
#include <Helpers.h>
#include <AnimationComponent.h>
#include <FSM.h>

class ScoreAppearingState final: public GameEngine::FSMState
{
public:
	ScoreAppearingState() = default;
	~ScoreAppearingState() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::AnimationComponent*) override {};
	virtual void Update(GameEngine::AnimationComponent* pBlackboard) override;

private:
	const int m_NumberOfEnterStateFrames = 3;
	const int m_HorizontalOffset = 1;
	const int m_FramesPerSec = 1;
	const int m_VerticalOffset = 0;

};

class ScoreWaitingState final : public GameEngine::FSMState
{
public:
	ScoreWaitingState() = default;
	~ScoreWaitingState() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::AnimationComponent*) override {};
	virtual void Update(GameEngine::AnimationComponent* pBlackboard) override;

private:
	const int m_NumberOfEnterStateFrames = 1;
	const int m_HorizontalOffset = 0;
	const int m_FramesPerSec = 1;
	const int m_VerticalOffset = 0;

};
class IsScoreWaiting final : public GameEngine::FSMCondition
{
public:
	IsScoreWaiting() = default;
	~IsScoreWaiting() = default;

	virtual bool Evaluate(GameEngine::AnimationComponent* pBlackboard) const override;

private:
	const float m_MaxWaitingTime = 2.5f;
};

