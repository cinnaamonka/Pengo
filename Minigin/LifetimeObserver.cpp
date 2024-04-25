#include "LifetimeObserver.h"

namespace GameEngine
{
	LifetimeObserver::LifetimeObserver(GameEngine::GameObject* pGameObject) :
		BaseComponent(pGameObject)
	{
	}

	void LifetimeObserver::Notify(const bool& message_from_subject)
	{
		GetGameObject()->SetIsDestroyed(message_from_subject);
	}

}
