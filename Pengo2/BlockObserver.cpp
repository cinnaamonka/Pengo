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

		if (glm::abs(message_from_subject.hitInfo.normal.y) > 0.9f && 
			glm::abs(message_from_subject.hitInfo.normal.x) < 0.1f) 
		{
			bool isMovingUp = message_from_subject.hitInfo.normal.y > 0; 

			baseBlock->SetPushSpeed(10.0f);

			glm::vec3 pushDirection = glm::vec3(0, isMovingUp ? 1 : -1, 0);

			baseBlock->PushBlock(pushDirection);

		}

		if (glm::abs(message_from_subject.hitInfo.normal.x) > 0.9f &&
			glm::abs(message_from_subject.hitInfo.normal.y) < 0.1f)
		{
			bool isMovingRight = message_from_subject.hitInfo.normal.x > 0;

			baseBlock->SetPushSpeed(10.0f);

			glm::vec3 pushDirection = glm::vec3(isMovingRight ? 1 : -1, 0, 0);

			baseBlock->PushBlock(pushDirection);
		}
		
	}
}
