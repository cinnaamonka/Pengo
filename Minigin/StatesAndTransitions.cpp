#include "StatesAndTransitions.h"
#include "TimeManager.h"

#include <iostream>

namespace GameEngine
{
	void IdleState::OnEnter(GameEngine::Blackboard* pBlackboard)
	{
		pBlackboard->ChangeData("NumberOfFrames", 1);
		pBlackboard->ChangeData("HorizontalOffset", 0);
		pBlackboard->ChangeData("VerticalOffset", 0);
	}

	void IdleState::OnExit(Blackboard* pBlackboard)
	{
		pBlackboard->ChangeData("WasInputGiven", false);
	}

	void IdleState::Update(GameEngine::Blackboard* pBlackboard)
	{
		AnimationUpdate(pBlackboard);

	}

	void RunningState::OnEnter(GameEngine::Blackboard* pBlackboard)
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

	void RunningState::OnExit(GameEngine::Blackboard* pBlackboard)
	{
		pBlackboard->ChangeData("WasInputGiven", false);
	}

	void RunningState::Update(GameEngine::Blackboard* pBlackboard)
	{
		AnimationUpdate(pBlackboard);

		pBlackboard->ChangeData("WasInputGiven", false);
	}

	void PushingState::OnEnter(GameEngine::Blackboard* pBlackboard)
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
	void PushingState::OnExit(GameEngine::Blackboard* pBlackboard)
	{
		pBlackboard->ChangeData("WasBlockPushed", false);
		pBlackboard->ChangeData("WasInputGiven", false);
	}
	void PushingState::Update(GameEngine::Blackboard* pBlackboard)
	{
		AnimationUpdate(pBlackboard);
		pBlackboard->ChangeData("WasBlockPushed", false);
	}
	void StaticBlockState::OnEnter(GameEngine::Blackboard* pBlackboard)
	{
		pBlackboard->ChangeData("NumberOfFrames", 1); 
		pBlackboard->ChangeData("HorizontalOffset", 0); 
		pBlackboard->ChangeData("VerticalOffset", 0); 
	}
	void StaticBlockState::OnExit(GameEngine::Blackboard*)
	{
	}
	void StaticBlockState::Update(GameEngine::Blackboard* pBlackboard)
	{
		pBlackboard = pBlackboard;

		AnimationUpdate(pBlackboard); 
	}

	void BreakingBlockState::OnEnter(GameEngine::Blackboard* pBlackboard)
	{
		pBlackboard->ChangeData("NumberOfFrames", 9);
		pBlackboard->ChangeData("HorizontalOffset", 1);
		pBlackboard->ChangeData("VerticalOffset", 0);
	}

	void BreakingBlockState::OnExit(GameEngine::Blackboard* pBlackboard)
	{
		pBlackboard->ChangeData("NumberOfFrames", 1);
		pBlackboard->ChangeData("HorizontalOffset", 9);
		pBlackboard->ChangeData("VerticalOffset", 0);
	}

	void BreakingBlockState::Update(GameEngine::Blackboard* pBlackboard)
	{
		AnimationUpdate(pBlackboard);
	}

	// conditions
	bool IsInputGiven::Evaluate(GameEngine::Blackboard* pBlackboard) const
	{
		bool inputWasGiven;
		pBlackboard->GetData("WasInputGiven", inputWasGiven);

		return inputWasGiven;
	}

	bool IsInputNotGiven::Evaluate(GameEngine::Blackboard* pBlackboard) const
	{
		bool inputWasGiven;
		pBlackboard->GetData("WasInputGiven", inputWasGiven);

		return !inputWasGiven;
	}

	bool IsBlockPushed::Evaluate(GameEngine::Blackboard* pBlackboard) const
	{
		bool wasBlockPushed;
		pBlackboard->GetData("WasBlockPushed", wasBlockPushed);

		return wasBlockPushed;
	}
	bool IsBlockNotPushed::Evaluate(GameEngine::Blackboard* pBlackboard) const
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
	
	void AnimationUpdate(GameEngine::Blackboard* pBlackboard)
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

	bool IsBlockBreaking::Evaluate(GameEngine::Blackboard* pBlackboard) const
	{
		bool wasBlockDedtroyed;
		pBlackboard->GetData("WasBlockDestroyed", wasBlockDedtroyed);

		return wasBlockDedtroyed;
	}

}
