#include "ScoreComponent.h"
#include "Observers.h"

namespace GameEngine
{
    ScoreComponent::ScoreComponent(GameObject* pGameObject) :
        BaseComponent(pGameObject), m_Score(0)
    {


    }
    void ScoreComponent::AddScore(int score)
    {
        m_Score += score;

        OnScoreChange->Notify(GetGameObject(),m_Score);
    }

    void ScoreComponent::RemoveScore(int score)
    {
        m_Score -= score;

        OnScoreChange->Notify(GetGameObject(),m_Score);
    }
    
}