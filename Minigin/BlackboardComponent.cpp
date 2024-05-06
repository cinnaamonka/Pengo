#include "BlackboardComponent.h"

namespace GameEngine
{
	BlackboardComponent::BlackboardComponent(GameEngine::GameObject* pGameObject) :
		BaseComponent(pGameObject)
	{
		AddData("NumberOfFrames", int());
		AddData("AnimationTime", float());
		AddData("FramesPerSec", 10);
		AddData("AnimationFrame", int());
		AddData("HorizontalOffset", int());
		AddData("VerticalOffset", int());
		AddData("MovementDirection", glm::vec3());
		AddData("Destroyed", bool());
	}
	void BlackboardComponent::Destroy()
	{
		GetGameObject()->SetIsDestroyed(true);
	}
}
