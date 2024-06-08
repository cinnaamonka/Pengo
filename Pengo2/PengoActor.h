#pragma once
#include <memory>
#include <GameObject.h>
#include "PlayerStatesAndTransitions.h"

class GameEngine::BlackboardComponent; 
class IdleState;
class RunningState;
class IsInputGiven;
class IsInputNotGiven;

class HitObserver;
class CollisionObserver;

class PengoActor final
{
public:
	PengoActor(const glm::vec3& position);
	~PengoActor(); 

	PengoActor(const PengoActor& other) = delete;
	PengoActor& operator=(const PengoActor& other) = delete;
	PengoActor(PengoActor&& other) noexcept = delete;
	PengoActor& operator=(PengoActor&& other) noexcept = delete;

	GameEngine::GameObject* GetReferenceToActor() const
	{
		return m_ReferenceToCharacterPengo;
	}


	std::unique_ptr<GameEngine::GameObject>& GetActorGameObject();
	static std::unique_ptr<GameEngine::GameObject> CreateControlledPengoEnemy(const glm::vec3& position);
private:

	std::unique_ptr<IdleState> m_IdleState;
	std::unique_ptr<RunningState> m_RunningState;
	std::unique_ptr<PushingState> m_PushingState;
	std::unique_ptr<PlayerDyingState> m_DyingState;

	std::unique_ptr<IsInputGiven> m_IsInputGiven;
	std::unique_ptr<IsInputNotGiven> m_IsNotInputGiven;
	std::unique_ptr<IsBlockPushed> m_IsBlockPushed;
	std::unique_ptr<IsBlockNotPushed> m_IsBlockNotPushed;
	std::unique_ptr<IsKilled> m_IsKilled;

	const int m_HorizontalAmountOfFrames = 8;
	const int m_VerticalAmountOfFrames = 3;
	const int m_HorAmountOfFramesControllerActor = 5;

	const int m_PengoActorSize = 20;

	GameEngine::GameObject* m_ReferenceToCharacterPengo;

	std::unique_ptr<GameEngine::GameObject> m_pActor;
};

