#include "ScoreSceneCommands.h"
#include <iostream>
#include <AnimationComponent.h>

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
    GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->SetWasInputGiven(true); 
}
