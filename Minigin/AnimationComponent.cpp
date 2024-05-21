#include "AnimationComponent.h"
#include "FSM.h"
#include "TransformComponent.h"

namespace GameEngine
{
	AnimationComponent::AnimationComponent(GameEngine::GameObject* pGameObject) :
		BaseComponent(pGameObject)
	{

	}

	void AnimationComponent::Update()
	{
		if (GetGameObject()->IsDestroyed() || GetGameObject() == NULL) return;

		ChangeTexture();
	}

	void AnimationComponent::ChangeTexture()
	{
		GameEngine::Rect previousDimensions = GetGameObject()->GetComponent<GameEngine::TransformComponent>()->GetDimensions();

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
		
		GetGameObject()->GetComponent<GameEngine::TransformComponent>()->SetDimensions(currentDimensions);
	}

	void AnimationComponent::Destroy()
	{
		GetGameObject()->SetIsDestroyed(true); 
	}

}