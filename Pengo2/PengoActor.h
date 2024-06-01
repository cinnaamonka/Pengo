#pragma once
#include <memory>
#include <GameObject.h>
#include "PlayerStatesAndTransitions.h"
#include <HealthObserver.h>

class GameEngine::BlackboardComponent; 
class IdleState;
class RunningState;
class IsInputGiven;
class IsInputNotGiven;

class HitObserver;
class CollisionObserver;
class HealthObserver;

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

	HitObserver* GetHitObserver() const;


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

	int m_HorizontalAmountOfFrames = 8;
	int m_VerticalAmountOfFrames = 3;

	GameEngine::GameObject* m_ReferenceToCharacterPengo;

	std::unique_ptr<GameEngine::GameObject> m_pActor;
};

