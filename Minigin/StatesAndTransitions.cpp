#include "StatesAndTransitions.h"
#include "TimeManager.h"

namespace GameEngine
{
	void IdleState::OnEnter(GameEngine::Blackboard* pBlackboard)
	{
		pBlackboard = pBlackboard;
	}

	void IdleState::OnExit(Blackboard* pBlackboard)
	{
		pBlackboard = pBlackboard;
		std::cout << " idle state on exit" << std::endl;
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

			animTime = 0.0f;
		}

		std::cout << " idle state update" << std::endl;
	}

	void RunningState::OnEnter(GameEngine::Blackboard* pBlackboard)
	{
		pBlackboard = pBlackboard; 
		std::cout << " running state on enter" << std::endl;
	}

	void RunningState::OnExit(GameEngine::Blackboard* pBlackboard)
	{
		pBlackboard = pBlackboard;
		std::cout << " running state on exit" << std::endl;
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

		animTime += TimeManager::GetElapsed();

		if (animTime >= 1.f / nrFramesPerSec)
		{
			++animFrame %= nrOfFrames;

			animTime = 0.0f;
		}

		std::cout << " running state on update" << std::endl;
	}

	bool IsInputGiven::Evaluate(GameEngine::Blackboard* pBlackboard) const
	{
		bool inputWasGiven;
		pBlackboard->GetData("WasInputGiven", inputWasGiven);

		std::cout << " is input given evaluate" << std::endl;

		return inputWasGiven;
	}

	bool IsInputNotGiven::Evaluate(GameEngine::Blackboard* pBlackboard) const
	{

		bool inputWasGiven;
		pBlackboard->GetData("WasInputGiven", inputWasGiven);

		return inputWasGiven;
	}
}
