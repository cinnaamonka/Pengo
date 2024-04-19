#include "PengoInputCommands.h"
#include <iostream>
#include <ActorComponent.h>
#include "Environment.h"

PushBlockCommand::PushBlockCommand(GameEngine::GameObject* gameObject)
	: GameObjectCommand(gameObject)
{

}

void PushBlockCommand::Execute()
{
	GetGameObject()->GetComponent<Environment>()->PushBlock();
}