#include "EnvironmentObserver.h"
#include "Environment.h"

EnvironmentObserver::EnvironmentObserver(GameEngine::GameObject* pGameObject):
	BaseComponent(pGameObject)
{
}

void EnvironmentObserver::Notify(const EventInfo& eventInfo)
{
	switch (eventInfo.event)
	{
	case Event::BlockIndexesChanged: 
		GetGameObject()->GetComponent<Environment>()->ResetBlocksIndexes();
		break;
	case Event::BlockDestroyed:
			GetGameObject()->GetComponent<Environment>()->DeleteBlockFromGame(eventInfo.index);
		break;
	default:
		break;
	}
}
