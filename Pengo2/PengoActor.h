#pragma once
#include <memory>
#include <GameObject.h>
#include <StatesAndTransitions.h>

class GameEngine::Blackboard;
class GameEngine::IdleState;
class GameEngine::RunningState;
class GameEngine::IsInputGiven;
class GameEngine::IsInputNotGiven;

class HitObserver;
class CollisionObserver;

class PengoActor final
{
public:
	PengoActor();
	~PengoActor(); 

	PengoActor(const PengoActor& other) = delete;
	PengoActor& operator=(const PengoActor& other) = delete;
	PengoActor(PengoActor&& other) noexcept = delete;
	PengoActor& operator=(PengoActor&& other) noexcept = delete;

	GameEngine::GameObject* GetReferenceToActor() const
	{
		return m_ReferenceToCharacterPengo;
	}

	CollisionObserver* GetCollisionObserver(); 
	HitObserver* GetHitObserver();
	std::unique_ptr<GameEngine::GameObject>& GetActorGameObject();

private:
	std::unique_ptr<GameEngine::GameObject> m_pActor;

	GameEngine::Blackboard* m_pBlackboard;

	GameEngine::IdleState* m_IdleState;
	GameEngine::RunningState* m_RunningState;

	GameEngine::IsInputGiven* m_IsInputGiven;
	GameEngine::IsInputNotGiven* m_IsNotInputGiven;

	int m_HorizontalAmountOfFrames = 8;
	int m_VerticalAmountOfFrames = 3;

	GameEngine::GameObject* m_ReferenceToCharacterPengo;
};

