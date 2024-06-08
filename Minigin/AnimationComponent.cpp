#include "AnimationComponent.h"

namespace GameEngine
{
	AnimationComponent::AnimationComponent(GameEngine::GameObject* pGameObject) :
		BaseComponent(pGameObject),
		m_AnimationFrame(0),
		m_HorizontalOffset(0),
		m_VerticalOffset(0),
		m_IsHorizontal(false),
		m_pTransformComponent(nullptr),
		m_IsDestroyed(false),
		m_NumberOfFrames(0),
		m_FramesPerSec(10),
		m_AnimationTime(0),
		m_MovementDirection{},
		m_TimeOffset(0),
		m_WasInputGiven(false),
		m_WasPushed(false),
		m_Pos{},
		m_Speed(0),
		m_IsChasing(false),
		m_IsVertical(false),
		m_ShouldFlyckering(false)
	{
		m_pTransformComponent = GetGameObject()->GetComponent<GameEngine::TransformComponent>();
	}

	void AnimationComponent::Update()
	{
		ChangeTexture();
	}

	void AnimationComponent::ChangeTexture()
	{
		GameEngine::Rect previousDimensions = m_pTransformComponent->GetDimensions();

		GameEngine::Rect currentDimensions =
		{
			m_HorizontalOffset * previousDimensions.width + m_AnimationFrame * previousDimensions.width,
			m_VerticalOffset * previousDimensions.height,
			previousDimensions.width,
			previousDimensions.height
		};

		if (m_IsHorizontal)
		{
			currentDimensions.left = m_HorizontalOffset * previousDimensions.width;
			currentDimensions.bottom = m_VerticalOffset * m_AnimationFrame * previousDimensions.height;
		}
		
		m_pTransformComponent->SetDimensions(currentDimensions);
	}

	void AnimationComponent::Destroy()
	{
		GetGameObject()->SetIsDestroyed(true); 
	}

}