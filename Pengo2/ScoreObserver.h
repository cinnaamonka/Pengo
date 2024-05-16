#pragma once
#include "memory"
#include <GameObject.h>

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <IObserver.h>
#include <Scene.h>

#include "ScoreStatesAndTransitions.h"

enum class ScoreType
{
	EggFound,
	EnemyKilled,
};
struct Score
{
	ScoreType type;
	glm::vec3 pos;
};
class ScoreObserver : public GameEngine::IObserver<Score>
{
public:

	ScoreObserver(GameEngine::Scene* scenePtr);
	~ScoreObserver() = default;
	ScoreObserver(const ScoreObserver& other) = delete;
	ScoreObserver(ScoreObserver&& other) = delete;
	ScoreObserver& operator=(const ScoreObserver& other) = delete;
	ScoreObserver& operator=(ScoreObserver&& other) = delete;

	void Notify(const Score& message_from_subject) override;

private:
	GameEngine::Scene* m_ScenePtr;

	int m_HorizontalAmountOfFrames = 2;

	std::unique_ptr<ScoreAppearingState> m_pScoreAppearing;
	std::unique_ptr<ScoreWaitingState> m_pScoreWaiting;;
	std::unique_ptr<IsScoreWaiting> m_pIsScoreWaiting;

};
