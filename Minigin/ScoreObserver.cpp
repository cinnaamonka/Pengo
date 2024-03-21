#include "ScoreObserver.h"
#include "TextComponent.h"

namespace GameEngine
{
	ScoreObserver::ScoreObserver(GameObject* pGameObject) :
		BaseComponent(pGameObject)
	{
		
	}

	void ScoreObserver::Notify(const int& message_from_subject)
	{
		GetGameObject()->GetComponent<TextComponent>()->SetText(std::to_string(message_from_subject));
	}


}