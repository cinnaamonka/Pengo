#pragma once
#include "memory"
#include <GameObject.h>

#include <glm/glm.hpp>
#include <IObserver.h>
#include <Scene.h>

#include "EggsStatesAndTransitions.h"

class EggObserver final : public GameEngine::IObserver<glm::vec3>
{
public:

	EggObserver(GameEngine::Scene* scenePtr);
	~EggObserver() = default;
	EggObserver(const EggObserver& other) = delete;
	EggObserver(EggObserver&& other) = delete;
	EggObserver& operator=(const EggObserver& other) = delete;
	EggObserver& operator=(EggObserver&& other) = delete;

	void Notify(const glm::vec3& message_from_subject) override;

private:
	GameEngine::Scene* m_pScene;

	std::unique_ptr<BreakingEggState> m_pBreakingEggState;
	std::unique_ptr<WaitingState> m_pWaitingEggState;
	std::unique_ptr<BrokenEggState> m_pBrokenEggState;
	std::unique_ptr<IsEggBroken> m_pIsEggBroken;
	std::unique_ptr<IsWaiting> m_pIsEggAnimationWaiting;

	int m_HorizontalAmountOfFrames = 4;

};

