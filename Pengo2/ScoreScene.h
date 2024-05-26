#pragma once
#include <BaseGame.h>

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
	void InitializeInputSystem(GameEngine::GameObject* gameActor) override; 
};




