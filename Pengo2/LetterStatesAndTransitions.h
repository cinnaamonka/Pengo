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
	virtual void Update(GameEngine::AnimationComponent*) override {};
};
class FlyckeringLetterState : public GameEngine::FSMState
{
public:
	FlyckeringLetterState() = default;
	~FlyckeringLetterState() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pAnimationComponent) override;
	virtual void OnExit(GameEngine::AnimationComponent*) override {};
	virtual void Update(GameEngine::AnimationComponent* pAnimationComponent) override;
};

class ShouldStartFlyckering : public GameEngine::FSMCondition
{
public:
	ShouldStartFlyckering() = default;
	~ShouldStartFlyckering() = default;

	virtual bool Evaluate(GameEngine::AnimationComponent* pAnimationComponent) const override;
};