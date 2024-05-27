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
        GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->SetVerticalOffset(0);
    }
    else
    {
        GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->SetHorizontalOffset(m_CurrentLetter - 80);
        GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->SetVerticalOffset(1);
    }

}
