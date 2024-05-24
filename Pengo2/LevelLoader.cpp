#include "LevelLoader.h"


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

bool LevelLoader::HasNextLevel() const
{
	return m_CurrentLevelIndex < m_TotalLevelsAmount;
}

std::function<std::unique_ptr<Game>()> LevelLoader::GetNextLevelLoader()
{
	return [this]() {
		return this->LoadLevel(m_CurrentLevelIndex++);
		};
}

