#include "HealthObserver.h"
#include "TextComponent.h"
#include "ActorComponent.h"
#include "AnimationComponent.h"

namespace GameEngine
{
	HealthObserver::HealthObserver(GameObject* pGameObject)
		:BaseComponent(pGameObject)
	{
		
	}
	void HealthObserver::Notify(const State& messageFromSubject)
	{
		switch (messageFromSubject)
		{
		case GameEngine::State::PlayerDied:
			GetGameObject()->GetComponent<AnimationComponent>()->SetIsDestroyed(true);

		}
		
	}
}