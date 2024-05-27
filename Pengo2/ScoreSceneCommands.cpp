#include "ScoreSceneCommands.h"
#include <iostream>
#include <AnimationComponent.h>
#include <FSM.h>

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
    }
    else
    {
        GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->SetHorizontalOffset(m_CurrentLetter - 80 + 1);
    }

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
