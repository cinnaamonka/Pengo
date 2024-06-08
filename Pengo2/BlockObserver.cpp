#include "BlockObserver.h"
#include "BaseBlock.h"

BlockObserver::BlockObserver(GameEngine::GameObject* pGameObject):
	BaseComponent(pGameObject)
{
}

void BlockObserver::Notify(const BlockCollisionInfo& message_from_subject)
{
	auto baseBlock = GetGameObject()->GetComponent<BaseBlock>();
	int baseBlockIndex = baseBlock->GetBlockIndex(); 

	if (baseBlockIndex == message_from_subject.index)
	{
		baseBlock->SetIsPushed(message_from_subject.isPushed);
	}

	if (baseBlockIndex == message_from_subject.index && message_from_subject.isPushed)
	{
		glm::vec3 direction = { 0,0,0 }; 

		if (glm::abs(message_from_subject.hitInfo.normal.y) > m_TopOffset &&
			glm::abs(message_from_subject.hitInfo.normal.x) < m_BottomOffset) 
		{
			bool isMovingUp = message_from_subject.hitInfo.normal.y > 0; 

			baseBlock->SetPushSpeed(m_PushSpeed);

			glm::vec3 pushDirection = glm::vec3(0, isMovingUp ? 1 : -1, 0);

			GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->SetMovementDirection(pushDirection);
			baseBlock->PushBlock(pushDirection);

		}

		if (glm::abs(message_from_subject.hitInfo.normal.x) > m_TopOffset &&
			glm::abs(message_from_subject.hitInfo.normal.y) < m_BottomOffset)
		{
			bool isMovingRight = message_from_subject.hitInfo.normal.x > 0;

			baseBlock->SetPushSpeed(m_PushSpeed);

			glm::vec3 pushDirection = glm::vec3(isMovingRight ? 1 : -1, 0, 0);
			GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->SetMovementDirection(pushDirection);

			baseBlock->PushBlock(pushDirection);
		}
		
	}
}
