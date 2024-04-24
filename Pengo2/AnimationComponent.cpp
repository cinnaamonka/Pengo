#include "AnimationComponent.h"
#include <FSM.h>
#include <TransformComponent.h>

AnimationComponent::AnimationComponent(GameEngine::GameObject* pGameObject,int framesPerSec):
	BaseComponent(pGameObject)
{
	m_pBlackboard = std::make_unique<GameEngine::Blackboard>();

	m_pBlackboard->AddData("NumberOfFrames", int());
	m_pBlackboard->AddData("AnimationTime", float());
	m_pBlackboard->AddData("FramesPerSec", framesPerSec);
	m_pBlackboard->AddData("AnimationFrame", int());
	m_pBlackboard->AddData("HorizontalOffset", int());
	m_pBlackboard->AddData("VerticalOffset", int());
	m_pBlackboard->AddData("MovementDirection", glm::vec3());

}

void AnimationComponent::Update()
{
	if (GetGameObject()->HasComponent<GameEngine::FSM>())
	{
		int currentAnimationFrame;
		GetGameObject()->GetComponent<GameEngine::FSM>()->GetBlackboard()->GetData("AnimationFrame", currentAnimationFrame);

		int currentHorizontalOffset;
		GetGameObject()->GetComponent<GameEngine::FSM>()->GetBlackboard()->GetData("HorizontalOffset", currentHorizontalOffset);

		int currentVerticalOffset;
		GetGameObject()->GetComponent<GameEngine::FSM>()->GetBlackboard()->GetData("VerticalOffset", currentVerticalOffset);

		ChangeTexture(currentAnimationFrame, currentHorizontalOffset, currentVerticalOffset);
	}
}

void AnimationComponent::ChangeTexture(int currentAnimationFrame, int currentHorizontalOffset, int currentVerticalOffset)
{
	GameEngine::Rect previousDimensions = GetGameObject()->GetComponent<GameEngine::TransformComponent>()->GetDimensions();

	GameEngine::Rect currentDimensions
	{
		currentHorizontalOffset * previousDimensions.width + currentAnimationFrame * previousDimensions.width,
		currentVerticalOffset * previousDimensions.height,
		previousDimensions.width,
		previousDimensions.height
	};
	GetGameObject()->GetComponent<GameEngine::TransformComponent>()->SetDimensions(currentDimensions);
}
