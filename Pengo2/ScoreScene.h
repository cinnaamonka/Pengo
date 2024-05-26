#pragma once
#include <BaseGame.h>
#include <memory>
#include "LetterStatesAndTransitions.h"
#include <Scene.h>

class GameEngine::GameObject;

class ScoreScene final : public GameEngine::BaseGame 
{
public:
	ScoreScene() = default;
	~ScoreScene() = default;

	ScoreScene(const ScoreScene& other) = delete;
	ScoreScene& operator=(const ScoreScene& other) = delete;
	ScoreScene(ScoreScene&& other) noexcept = delete;
	ScoreScene& operator=(ScoreScene&& other) noexcept = delete;

	void Initialize(int finalScore); 
	bool IsLevelComplete() override { return false; };

	void ResetLevel() override {};
private:
	void AddLetter(const glm::vec3& position, GameEngine::Scene* scene);
private:
	void InitializeInputSystem(GameEngine::GameObject* gameActor) override; 
	std::unique_ptr<StaticLetterState> m_pStaticLetterState;
	std::unique_ptr<FlyckeringLetterState> m_pFlyckeringLetterState;
	std::unique_ptr<ShouldStartFlyckering> m_pShouldStartFlyckering;
};




