#pragma once
#include <Helpers.h>
#include <FSM.h>


class StaticBlockState : public GameEngine::FSMState
{
public:
	StaticBlockState() = default;
	~StaticBlockState() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::AnimationComponent*) override;
	virtual void Update(GameEngine::AnimationComponent* pBlackboard) override;

};
class FlickeringBlockState : public GameEngine::FSMState
{
public:
	FlickeringBlockState() = default;
	~FlickeringBlockState() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::AnimationComponent*) override {};
	virtual void Update(GameEngine::AnimationComponent* pBlackboard) override;

};

class BreakingBlockState : public GameEngine::FSMState
{
public:
	BreakingBlockState() = default;
	~BreakingBlockState() = default;

	virtual void OnEnter(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::AnimationComponent* pBlackboard) override;
	virtual void Update(GameEngine::AnimationComponent* pBlackboard) override;

};

class IsBlockBreaking : public GameEngine::FSMCondition
{
public:
	IsBlockBreaking() = default;
	~IsBlockBreaking() = default;

	virtual bool Evaluate(GameEngine::AnimationComponent* pBlackboard) const override;
};
class IsBlockNotBreaking : public GameEngine::FSMCondition
{
public:
	IsBlockNotBreaking() = default;
	~IsBlockNotBreaking() = default;

	virtual bool Evaluate(GameEngine::AnimationComponent* pBlackboard) const override;
};

class IsBlockFinishedFlickering : public GameEngine::FSMCondition
{
public:
	IsBlockFinishedFlickering() = default;
	~IsBlockFinishedFlickering() = default;

	virtual bool Evaluate(GameEngine::AnimationComponent* pBlackboard) const override;
};

