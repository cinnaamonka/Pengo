#pragma once
#include "GameObject.h"

class IEnemyAnimationState
{
public:
    virtual void HandleInput(GameEngine::GameObject* bossObj) = 0;
    virtual void Update(GameEngine::GameObject* bossObj) = 0;
    virtual ~IEnemyAnimationState() = default; 
};

class EnemyPatrolState : public IEnemyAnimationState
{
public:
    virtual void HandleInput(GameEngine::GameObject* bossObj) override;
    virtual void Update(GameEngine::GameObject* bossObj) override;
    virtual ~EnemyPatrolState() = default;
};

class EnemyDyingState : public IEnemyAnimationState
{
public:
    virtual void HandleInput(GameEngine::GameObject* bossObj) override;
    virtual void Update(GameEngine::GameObject* bossObj) override;
    virtual ~EnemyDyingState() = default;
};