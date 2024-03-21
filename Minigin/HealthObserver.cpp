#include "HealthObserver.h"
#include "TextComponent.h"
#include "ActorComponent.h"

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
			GetGameObject()->GetComponent<TextComponent>()->SetText("Player died!");
		}
		
	}
	void HealthObserver::Notify(const int& messageFromSubject)
	{
		GetGameObject()->GetComponent<TextComponent>()->SetText(std::to_string(messageFromSubject));
	}
}