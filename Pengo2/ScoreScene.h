#pragma once
#include <BaseGame.h>
#include <memory>
#include "LetterStatesAndTransitions.h"
#include <Scene.h>
#include <Font.h>

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
	std::unique_ptr<GameEngine::GameObject> AddLetter(const glm::vec3& position); 
	void AddText(const glm::vec3& position, const std::string& text, GameEngine::Scene* scene,std::shared_ptr<GameEngine::Font> font);   
	
private:
	void InitializeInputSystem(GameEngine::GameObject* gameActor) override; 
	
	std::unique_ptr<StaticLetterState> m_pStaticLetterState;
	std::unique_ptr<FlyckeringLetterState> m_pFlyckeringLetterState;
	std::unique_ptr<ShouldStartFlyckering> m_pShouldStartFlyckering;
	std::unique_ptr<ShouldStopFlyckering> m_pShouldStopFlyckering;
	GameEngine::GameObject* m_pFirstLetter;
	GameEngine::GameObject* m_pSecondLetter;
	GameEngine::GameObject* m_pThirdLetter;
};




