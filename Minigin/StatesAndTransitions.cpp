#include "StatesAndTransitions.h"
#include "TimeManager.h"
#include <iostream>

namespace GameEngine
{
	void IdleState::OnEnter(GameEngine::BlackboardComponent* pBlackboard)
	{
		pBlackboard->ChangeData("NumberOfFrames", 1);
		pBlackboard->ChangeData("HorizontalOffset", 0);
		pBlackboard->ChangeData("VerticalOffset", 0);
	}

	void IdleState::OnExit(BlackboardComponent* pBlackboard)
	{
		pBlackboard->ChangeData("WasInputGiven", false);
	}

	void IdleState::Update(GameEngine::BlackboardComponent* pBlackboard)
	{
		AnimationUpdate(pBlackboard);

	}

	void RunningState::OnEnter(GameEngine::BlackboardComponent* pBlackboard)
	{
		glm::vec3 movementDirection;
		pBlackboard->GetData("MovementDirection", movementDirection);

		if (movementDirection.x > 0 || movementDirection.x < 0)
		{
			pBlackboard->ChangeData("HorizontalOffset", 2);
		}
		else if (movementDirection.y < 0)
		{
			pBlackboard->ChangeData("HorizontalOffset", 4);
		}
		else if (movementDirection.y > 0)
		{
			pBlackboard->ChangeData("HorizontalOffset", 0);
		}
		pBlackboard->ChangeData("NumberOfFrames", 2);
		pBlackboard->ChangeData("VerticalOffset", 0);
	}

	void RunningState::OnExit(GameEngine::BlackboardComponent* pBlackboard)
	{
		pBlackboard->ChangeData("WasInputGiven", false);
	}

	void RunningState::Update(GameEngine::BlackboardComponent* pBlackboard)
	{
		AnimationUpdate(pBlackboard);

		pBlackboard->ChangeData("WasInputGiven", false);
	}

	void PushingState::OnEnter(GameEngine::BlackboardComponent* pBlackboard)
	{
		glm::vec3 movementDirection;
		pBlackboard->GetData("MovementDirection", movementDirection);

		if (movementDirection.x > 0 || movementDirection.x < 0)
		{
			pBlackboard->ChangeData("HorizontalOffset", 2);
		}
		else if (movementDirection.y < 0)
		{
			pBlackboard->ChangeData("HorizontalOffset", 4);
		}
		else if (movementDirection.y > 0)
		{
			pBlackboard->ChangeData("HorizontalOffset", 0);
		}
		pBlackboard->ChangeData("NumberOfFrames", 2);
		pBlackboard->ChangeData("VerticalOffset", 1);
	}
	void PushingState::OnExit(GameEngine::BlackboardComponent* pBlackboard)
	{
		pBlackboard->ChangeData("WasBlockPushed", false);
		pBlackboard->ChangeData("WasInputGiven", false);
	}
	void PushingState::Update(GameEngine::BlackboardComponent* pBlackboard)
	{
		AnimationUpdate(pBlackboard);
		pBlackboard->ChangeData("WasBlockPushed", false);
	}
	void StaticBlockState::OnEnter(GameEngine::BlackboardComponent* pBlackboard)
	{
		pBlackboard->ChangeData("NumberOfFrames", 1); 
		pBlackboard->ChangeData("HorizontalOffset", 0); 
		pBlackboard->ChangeData("VerticalOffset", 0); 
	}
	void StaticBlockState::OnExit(GameEngine::BlackboardComponent* pBlackboard)
	{
		pBlackboard->ChangeData("WasBlockDestroyed", false);
	}
	void StaticBlockState::Update(GameEngine::BlackboardComponent* pBlackboard)
	{
		pBlackboard = pBlackboard;

		AnimationUpdate(pBlackboard); 
	}

	void BreakingBlockState::OnEnter(GameEngine::BlackboardComponent* pBlackboard)
	{
		pBlackboard->ChangeData("NumberOfFrames", 9);
		pBlackboard->ChangeData("FramesPerSec", 10);
		pBlackboard->ChangeData("HorizontalOffset", 1);
		pBlackboard->ChangeData("VerticalOffset", 0);
	}

	void BreakingBlockState::OnExit(GameEngine::BlackboardComponent* pBlackboard)
	{
		bool isDestroyed;
		pBlackboard->GetData("Destroyed", isDestroyed);
	
		if(isDestroyed)
		{
				pBlackboard->Destroy();
		}
	
	}

	void BreakingBlockState::Update(GameEngine::BlackboardComponent* pBlackboard)
	{
		AnimationUpdate(pBlackboard);

		int currentAnimationFrame;
		pBlackboard->GetData("AnimationFrame", currentAnimationFrame);

		int numberOfFrames;
		pBlackboard->GetData("NumberOfFrames", numberOfFrames);

		if (currentAnimationFrame == numberOfFrames-1)
		{
			pBlackboard->ChangeData("WasBlockDestroyed", false);
			pBlackboard->ChangeData("Destroyed", true);
		}
	}

	// conditions
	bool IsInputGiven::Evaluate(GameEngine::BlackboardComponent* pBlackboard) const
	{
		bool inputWasGiven;
		pBlackboard->GetData("WasInputGiven", inputWasGiven);

		return inputWasGiven;
	}

	bool IsInputNotGiven::Evaluate(GameEngine::BlackboardComponent* pBlackboard) const
	{
		bool inputWasGiven;
		pBlackboard->GetData("WasInputGiven", inputWasGiven);

		return !inputWasGiven;
	}

	bool IsBlockPushed::Evaluate(GameEngine::BlackboardComponent* pBlackboard) const
	{
		bool wasBlockPushed;
		pBlackboard->GetData("WasBlockPushed", wasBlockPushed);

		return wasBlockPushed;
	}
	bool IsBlockNotPushed::Evaluate(GameEngine::BlackboardComponent* pBlackboard) const
	{
		bool wasBlockPushed;
		pBlackboard->GetData("WasBlockPushed", wasBlockPushed);

		float animTime = 0.0f;
		pBlackboard->GetData("AnimationTime", animTime);

		if (animTime <= 1.f && wasBlockPushed)
		{
			return false;
		}
		return true;
	}
	
	void AnimationUpdate(GameEngine::BlackboardComponent* pBlackboard)
	{
		float animTime;
		int nrFramesPerSec;
		int animFrame;
		int nrOfFrames;

		pBlackboard->GetData("NumberOfFrames", nrOfFrames);
		pBlackboard->GetData("AnimationTime", animTime);
		pBlackboard->GetData("FramesPerSec", nrFramesPerSec);
		pBlackboard->GetData("AnimationFrame", animFrame);

		animTime += GameEngine::TimeManager::GetElapsed();

		if (animTime >= 1.f / nrFramesPerSec)
		{
			++animFrame %= nrOfFrames;

			animTime = 0;

			pBlackboard->ChangeData("AnimationFrame", animFrame);
			pBlackboard->ChangeData("AnimationTime", animTime);
		}
		pBlackboard->ChangeData("AnimationTime", animTime);
	}

	bool IsBlockBreaking::Evaluate(GameEngine::BlackboardComponent* pBlackboard) const
	{
		bool wasBlockDedtroyed;
		pBlackboard->GetData("WasBlockDestroyed", wasBlockDedtroyed);

		return wasBlockDedtroyed;
	}

	bool IsBlockNotBreaking::Evaluate(GameEngine::BlackboardComponent* pBlackboard) const
	{
		bool wasBlockDedtroyed;
		pBlackboard->GetData("WasBlockDestroyed", wasBlockDedtroyed);

		return !wasBlockDedtroyed; 
	}

}
