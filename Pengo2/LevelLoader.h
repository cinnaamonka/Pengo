#pragma once
#include <memory>
#include "Game.h"
#include "ScoreScene.h"
#include "StartScreen.h"
#include <functional>

class LevelLoader final
{
public:
	LevelLoader(int totalLevels);
	~LevelLoader() = default;

	LevelLoader(const LevelLoader& other) = delete;
	LevelLoader(LevelLoader&& other) noexcept = delete;
	LevelLoader& operator=(const LevelLoader& other) = delete;
	LevelLoader& operator=(LevelLoader&& other) noexcept = delete;

	std::unique_ptr<Game> LoadLevel(int levelIndex,int maxLevels);
	std::unique_ptr<ScoreScene> LoadFinalScene(int finalScore); 
	std::unique_ptr<StartScreen> LoadStartScene();
	bool HasNextLevel() const;

	std::function<std::unique_ptr<Game>()> GetNextLevelLoader();
	std::function<std::unique_ptr<ScoreScene>()> GetFinalScene();
	std::function<std::unique_ptr<StartScreen>()> GetStartScreen();
	
private:
	int m_TotalLevelsAmount;
	int m_CurrentLevelIndex;
};

