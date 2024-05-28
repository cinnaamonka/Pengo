#pragma once
#include <BaseGame.h>
#include <memory>
#include "Letter.h"
#include <Scene.h>
#include <Font.h>
#include <Subject.h>
#include "Structs.h"


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
	void AddLeadersList(GameEngine::Scene* scene, std::shared_ptr<GameEngine::Font> font);
private:
	void InitializeInputSystem(GameEngine::GameObject*) override; 

	GameEngine::Subject<ScoreBoardData> m_AddScoreToScoreboardEvent; 

	std::unique_ptr<GameEngine::GameObject> m_pFinalPlayerScore;

	std::vector<GameEngine::GameObject*> m_pLetters;
	int m_CurrentLetterIndex = 0;
	int m_Score;

	const glm::vec3& m_ScoreLablePosition = glm::vec3(150, 150, 0);
	const glm::vec3& m_InitialsLabelPosition = glm::vec3(170, 100, 0);
	const glm::vec3& m_NameLabelPosition = glm::vec3(400, 150, 0);
	const glm::vec3& m_CurrentScorePosition = glm::vec3(160, 180, 0);
	const glm::vec3& m_LeaderBordPositionPosition = glm::vec3(160, 270, 0);
	const glm::vec3& m_LeadersPosition = glm::vec3(100, 270, 0);
	const glm::vec3& m_LettersPosition = glm::vec3(400, 180, 0);
	const glm::vec3& m_SubNameLabelPosition = glm::vec3(150, 230, 0);
	const glm::vec3& m_SubScoreLabelPosition = glm::vec3(400, 230, 0);

	const int m_LettersAmount = 3;
	const int m_LeadersAmount = 5;
	const int m_LettersInTextureRow = 16;
	const int m_LettersInTextureColumn = 4;
};




