#pragma once
#include <Helpers.h>
#include <BlackboardComponent.h>

class StaticBlockState : public GameEngine::FSMState
{
public:
	StaticBlockState() = default;
	~StaticBlockState() = default;

	virtual void OnEnter(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::BlackboardComponent*) override;
	virtual void Update(GameEngine::BlackboardComponent* pBlackboard) override;

};
class FlickeringBlockState : public GameEngine::FSMState
{
public:
	FlickeringBlockState() = default;
	~FlickeringBlockState() = default;

	virtual void OnEnter(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::BlackboardComponent*) override {};
	virtual void Update(GameEngine::BlackboardComponent* pBlackboard) override;

};

class BreakingBlockState : public GameEngine::FSMState
{
public:
	BreakingBlockState() = default;
	~BreakingBlockState() = default;

	virtual void OnEnter(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void Update(GameEngine::BlackboardComponent* pBlackboard) override;

};

class IsBlockBreaking : public GameEngine::FSMCondition
{
public:
	IsBlockBreaking() = default;
	~IsBlockBreaking() = default;

	virtual bool Evaluate(GameEngine::BlackboardComponent* pBlackboard) const override;
};
class IsBlockNotBreaking : public GameEngine::FSMCondition
{
public:
	IsBlockNotBreaking() = default;
	~IsBlockNotBreaking() = default;

	virtual bool Evaluate(GameEngine::BlackboardComponent* pBlackboard) const override;
};

class IsBlockFinishedFlickering : public GameEngine::FSMCondition
{
public:
	IsBlockFinishedFlickering() = default;
	~IsBlockFinishedFlickering() = default;

	virtual bool Evaluate(GameEngine::BlackboardComponent* pBlackboard) const override;
};

