#include "HealthObserver.h"
#include "TextComponent.h"
#include "ActorComponent.h"
#include "BlackboardComponent.h"

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
			GetGameObject()->GetComponent<BlackboardComponent>()->ChangeData("IsKilled", true);
		}
		
	}
	void HealthObserver::Notify(const int&)
	{
		//GetGameObject()->GetComponent<TextComponent>()->SetText(std::to_string(messageFromSubject));
	}
}