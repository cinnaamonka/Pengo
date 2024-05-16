#pragma once
#include <Helpers.h>
#include <AnimationComponent.h>
#include <FSM.h>

class ScoreAppearingState : public GameEngine::FSMState
{
public:
	ScoreAppearingState() = default;
	~ScoreAppearingState() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::AnimationComponent*) override {};
	virtual void Update(GameEngine::AnimationComponent* pBlackboard) override;

};

class ScoreWaitingState : public GameEngine::FSMState
{
public:
	ScoreWaitingState() = default;
	~ScoreWaitingState() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::AnimationComponent*) override {};
	virtual void Update(GameEngine::AnimationComponent* pBlackboard) override;

};
class IsScoreWaiting : public GameEngine::FSMCondition
{
public:
	IsScoreWaiting() = default;
	~IsScoreWaiting() = default;

	virtual bool Evaluate(GameEngine::AnimationComponent* pBlackboard) const override;
};

