#include "ScoreSceneCommands.h"
#include <iostream>
#include <AnimationComponent.h>
#include "ScoreSceneCommands.h"
#include "Letter.h"
#include <numeric>
#include <FSM.h>
#include <TransformComponent.h>
#include <InputManager.h>

ChangeLetterCommand::ChangeLetterCommand(GameEngine::GameObject* gameObject):
	GameObjectCommand(gameObject)
{

}

void ChangeLetterCommand::Execute()
{

    if (m_CurrentLetter == 'Z')
    {
        m_CurrentLetter = 'A';
    }
    else 
    {
        m_CurrentLetter++;
    }

    if (m_CurrentLetter < 'P')
    {
        GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->SetHorizontalOffset(m_CurrentLetter - 65 + 1);

        int currentVerticalOffset = GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->GetVerticalOffset();

        switch (currentVerticalOffset)
        {
        case 1:
            GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->SetVerticalOffset(0);
            break;
        case 3:
            GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->SetVerticalOffset(2);
            break;
        default:
            break;
        }
    }
    else
    {
        GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->SetHorizontalOffset(m_CurrentLetter - 80);

        int currentVerticalOffset = GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->GetVerticalOffset();

        switch (currentVerticalOffset)
        {
        case 0:
            GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->SetVerticalOffset(1);
            break;
        case 2:
            GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->SetVerticalOffset(3);
            break;
        default:
            break;
        }
       
    }

    GetGameObject()->GetComponent<Letter>()->SetCurrentLetter(m_CurrentLetter);
}

SumbitNameCommand::SumbitNameCommand(GameEngine::GameObject* gameObject) :
    GameObjectCommand(gameObject)

{
}

void SumbitNameCommand::Execute()
{
    int currentVerticalOffset = GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->GetVerticalOffset(); 
       
    switch (currentVerticalOffset)
    {
    case 0:
    case 1:
        GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->SetVerticalOffset(currentVerticalOffset);
        break;
	case 2:
    case 3:
            GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->SetVerticalOffset(currentVerticalOffset - 2);
    default:
        break;
    }
  
    GetGameObject()->RemoveComponent<GameEngine::FSM>();
}

SwitchToNextLetter::SwitchToNextLetter(std::vector<GameEngine::GameObject*>& letters, int& currentLetterIndex,int score, const glm::vec3& position,
    GameEngine::Subject<ScoreBoardData>* subject) :
    GameObjectCommand(letters[currentLetterIndex]),
    m_CurrentLetterIndex(currentLetterIndex),
    m_pLetters(letters),
    m_Score(score),
    m_Position(position),
    m_Subject(subject)
{

}

void SwitchToNextLetter::Execute()
{
    auto currentLetter = m_pLetters[m_CurrentLetterIndex]->GetComponent<Letter>()->GetCurrentLetter(); 
    GameEngine::UpdateLevelFile("Letter" + std::to_string(m_CurrentLetterIndex), std::string(1, currentLetter), "Score.json"); 

    if (m_CurrentLetterIndex == m_LastLetterIndex)
    {
        m_CurrentLetterIndex = -1;

        std::string name{};
        for (int i = 0; i < m_MaxLetters; ++i) {
            name += m_pLetters[i]->GetComponent<Letter>()->GetCurrentLetter();
        }

        GameEngine::AddScoreToFile("Score.json", m_Score, name);

        m_Subject->CreateMessage(ScoreBoardData{ m_Position,name });

    

         return;
    }
    else
    {
        m_CurrentLetterIndex++;
        m_pLetters[m_CurrentLetterIndex]->GetComponent<Letter>()->AddAnimation();
        m_pLetters[m_CurrentLetterIndex]->GetComponent<Letter>()->AddNewInput();
       
    }
   
}

