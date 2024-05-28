#pragma once
#include <BaseGame.h>
#include <memory>
#include "Letter.h"
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
	void ShowLeaderBord(GameEngine::Scene* scene,std::shared_ptr<GameEngine::Font> font,const glm::vec3& pos);
	
private:
	void InitializeInputSystem(GameEngine::GameObject*) override; 



	std::vector<GameEngine::GameObject*> m_pLetters;
	int m_CurrentLetterIndex = 0;
	int m_Score;
};




