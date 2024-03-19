#include "ScoreComponent.h"

namespace GameEngine
{
    ScoreComponent::ScoreComponent(GameObject* pGameObject) :
        BaseComponent(pGameObject), m_Score(0)
    {

    }
    void ScoreComponent::AddScore(int amount)
    {
        m_Score += amount;
        GetGameObject()->OnNotify(GameEngine::Event::ChangeScore);
    }
}