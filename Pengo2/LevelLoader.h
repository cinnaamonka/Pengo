#pragma once
#include <memory>
#include "Game.h"
#include "ScoreScene.h"
#include <functional>
#include "Structs.h"
#include <Helpers.h>


class LevelLoader final
{
public:
	LevelLoader(int totalLevels);
	~LevelLoader() = default;

	LevelLoader(const LevelLoader& other) = delete;
	LevelLoader(LevelLoader&& other) noexcept = delete;
	LevelLoader& operator=(const LevelLoader& other) = delete;
	LevelLoader& operator=(LevelLoader&& other) noexcept = delete;

	std::unique_ptr<Game> LoadLevel(int levelIndex);
	std::unique_ptr<ScoreScene> LoadFinalScene(int finalScore); 
	bool HasNextLevel() const;

	std::function<std::unique_ptr<Game>()> GetNextLevelLoader();
	std::function<std::unique_ptr<ScoreScene>()> GetFinalScene();
	
private:
	int m_TotalLevelsAmount;
	int m_CurrentLevelIndex;
};

