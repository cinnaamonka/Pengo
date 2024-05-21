#pragma once
#include <Helpers.h>
#include <FSM.h>

class VibratingState : public GameEngine::FSMState
{
public:
	VibratingState() = default;
	~VibratingState() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::AnimationComponent*) override {};
	virtual void Update(GameEngine::AnimationComponent* pBlackboard) override;

};
class StopVibrating : public GameEngine::FSMState
{
public:
	StopVibrating() = default;
	~StopVibrating() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::AnimationComponent*) override {};
	virtual void Update(GameEngine::AnimationComponent*) override {};

};

class HasFinishedVibrating : public GameEngine::FSMCondition
{
public:
	HasFinishedVibrating() = default;
	~HasFinishedVibrating() = default;

	virtual bool Evaluate(GameEngine::AnimationComponent* pBlackboard) const override;
};
class IsVibrating : public GameEngine::FSMCondition
{
public:
	IsVibrating() = default;
	~IsVibrating() = default;

	virtual bool Evaluate(GameEngine::AnimationComponent* pBlackboard) const override;
};

