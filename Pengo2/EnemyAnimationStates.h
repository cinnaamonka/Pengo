#pragma once
#include "GameObject.h"

class IEnemyAnimationState 
{
public:
    virtual void HandleInput(GameEngine::GameObject* bossObj) = 0;
    virtual void Update(GameEngine::GameObject* bossObj) = 0;
    virtual ~IEnemyAnimationState() = default; 
};

class EnemyPatrolState final: public IEnemyAnimationState
{
public:
    virtual void HandleInput(GameEngine::GameObject* bossObj) override;
    virtual void Update(GameEngine::GameObject* bossObj) override;
    virtual ~EnemyPatrolState() = default;

private:
    const int m_NumberOfEnterStateFrames = 2;
    const int m_HorizontalOffset = 0;
    const int m_VerticalOffset = 1;
};

class EnemyDyingState final: public IEnemyAnimationState
{
public:
    virtual void HandleInput(GameEngine::GameObject* bossObj) override;
    virtual void Update(GameEngine::GameObject* bossObj) override;
    virtual ~EnemyDyingState() = default;

private:
    const int m_NumberOfEnterStateFrames = 2;
    const int m_VerticalOffset = 4;
    const int m_FramesPerSec = 1;
    const int m_HorizontalDeathOffset = 2;
    const int m_VerticalTopDeathOffset = 0;
    const int m_VerticalBottomDeathOffset = 4;
};