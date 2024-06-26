#include "PengoInputCommands.h"
#include <SoundServiceLocator.h>
#include "Environment.h"

PushBlockCommand::PushBlockCommand(GameEngine::GameObject* gameObject, GameEngine::GameObject* actor) :
	GameObjectCommand(gameObject),
	m_pActor(actor)
{
}

void PushBlockCommand::Execute()
{
	GetGameObject()->GetComponent<Environment>()->PushBlock(m_pActor);
}

StopPushCommand::StopPushCommand(GameEngine::GameObject* gameObject):
	GameObjectCommand(gameObject)
{
}

void StopPushCommand::Execute()
{
	GetGameObject()->GetComponent<Environment>()->SetBordersUntouched();
}

SkipLevelCommand::SkipLevelCommand(GameEngine::GameObject* gameObject, std::function<void()> func):
	GameObjectCommand(gameObject),
	m_pFunction(func)
{

}

void SkipLevelCommand::Execute()
{
	m_pFunction();
}

MuteSoundCommand::MuteSoundCommand(GameEngine::GameObject* gameObject):
	GameObjectCommand(gameObject)
{
	
}

void MuteSoundCommand::Execute()
{
	m_IsMuted = !m_IsMuted;

	if (m_IsMuted)
	{
		GameEngine::SoundServiceLocator::GetInstance().GetSoundSystemInstance().Pause();
	}
	else
	{
		GameEngine::SoundServiceLocator::GetInstance().GetSoundSystemInstance().Resume();
	}
	
}

BreakBlockCommand::BreakBlockCommand(GameEngine::GameObject* gameObject) :
	GameObjectCommand(gameObject)
{
}

void BreakBlockCommand::Execute()
{
	GetGameObject()->GetComponent<Environment>()->EnemyPlayerBreakBlock(); 
}
