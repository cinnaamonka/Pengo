#pragma once
#include "memory"
#include <GameObject.h>

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <IObserver.h>
#include <Scene.h>

#include "EggsStatesAndTransitions.h"

class EggObserver : public GameEngine::IObserver<glm::vec3>
{
public:
	//rule of 5
	EggObserver(GameEngine::Scene* scenePtr);
	~EggObserver() = default;
	EggObserver(const EggObserver& other) = delete;
	EggObserver(EggObserver&& other) = delete;
	EggObserver& operator=(const EggObserver& other) = delete;
	EggObserver& operator=(EggObserver&& other) = delete;

	void Notify(const glm::vec3& message_from_subject) override;

private:
	GameEngine::Scene* m_ScenePtr;
	std::unique_ptr<BreakingEggState> m_BreakingEggState;
	std::unique_ptr<WaitingState> m_WaitingEggState;
	std::unique_ptr<BrokenEggState> m_pBrokenEggState;
	std::unique_ptr<IsEggBroken> m_IsEggBroken;
	std::unique_ptr<IsWaiting> m_IsEggAnimationWaiting;
	int m_HorizontalAmountOfFrames = 4;

};

