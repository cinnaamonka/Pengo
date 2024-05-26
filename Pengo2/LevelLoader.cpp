#include "LevelLoader.h"
#include <json.hpp>
#include <Helpers.h>

LevelLoader::LevelLoader(int totalLevels) :
	m_TotalLevelsAmount(totalLevels),
	m_CurrentLevelIndex(0)
{}

std::unique_ptr<Game> LevelLoader::LoadLevel(int levelIndex)
{
	std::unique_ptr<Game> pGame = std::make_unique<Game>();
	pGame->Initialize(levelIndex);
	return pGame;
}

std::unique_ptr<ScoreScene> LevelLoader::LoadFinalScene(int finalScore)
{
	std::unique_ptr<ScoreScene> finalScene = std::make_unique<ScoreScene>();  
	finalScene->Initialize(finalScore); 
	return finalScene; 
}

bool LevelLoader::HasNextLevel() const
{
	return m_CurrentLevelIndex < m_TotalLevelsAmount;
}

std::function<std::unique_ptr<Game>()> LevelLoader::GetNextLevelLoader()
{
	return [this]()
		{
		return this->LoadLevel(m_CurrentLevelIndex++);
		};
}
std::function<std::unique_ptr<ScoreScene>()> LevelLoader::GetFinalScene()
{
	const std::string& tag = "score";
	const std::string& fileName = "Score.json";
	int score = GameEngine::GetFieldFromFile<int>(tag, fileName);

	return [this,score]()
		{
			return this->LoadFinalScene(score); 
		};
}

