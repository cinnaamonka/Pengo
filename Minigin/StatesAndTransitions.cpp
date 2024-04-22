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

			pBlackboard->ChangeData("AnimationFrame", animFrame);

			animTime = 0.0f;

			pBlackboard->ChangeData("AnimationTime", animTime);
		}
		pBlackboard->ChangeData("AnimationTime", animTime);
	}

	void RunningState::OnEnter(GameEngine::Blackboard* pBlackboard)
	{
		glm::vec3 movementDirection;
		pBlackboard->GetData("MovementDirection", movementDirection);
	  
		if (movementDirection.x > 0 )
		{
			pBlackboard->ChangeData("HorizontalOffset", 2);
		}
		else if (movementDirection.x < 0)
		{
			pBlackboard->ChangeData("HorizontalOffset", 6);
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

			pBlackboard->ChangeData("AnimationFrame", animFrame);

			animTime = 0.0f;

			pBlackboard->ChangeData("AnimationTime", animTime);
		}
		pBlackboard->ChangeData("AnimationTime", animTime);
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
	}
	void PushingState::Update(GameEngine::Blackboard* pBlackboard)
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
		pBlackboard->ChangeData("WasBlockPushed", false);
	}

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
}
