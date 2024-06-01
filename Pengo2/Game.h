#pragma once
#include <BaseGame.h>
#include <Engine.h>
#include <memory>
#include <functional>

#include <Scene.h>
#include <SceneManager.h>
#include <GameObject.h>

#include "Environment.h"
#include "PengoActor.h"
#include "EnemyActor.h"
#include "EggObserver.h"
#include "EnemyManager.h"
#include <InputManager.h>
#include "EnvironmentObserver.h"
#include "ScoreObserver.h"
#include <IObserver.h>
#include <Helpers.h>
#include <HUD.h>
#include <SDL_mixer.h>
#include <mutex>

class Game final :public GameEngine::BaseGame, public GameEngine::IObserver<GameEngine::State>
{
public:
	Game() = default;
	~Game() override {};

	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) noexcept = delete;
	Game& operator=(Game&& other) noexcept = delete;

	void Initialize(int levelIndex,int maxLevelsCount);
	bool IsLevelComplete() override;

	void ResetLevel() override
	{
		m_IsLevelComplete = false;
	}

	void Notify(const GameEngine::State& messageFromSubject) override;

private:
	void InitializeInputSystem(GameEngine::GameObject* gameActor, GameEngine::GameModes gameMode,int deviceIndex) override;
	void LoadSounds();
	void InitializeSinglePlayerInput(GameEngine::InputManager& input,GameEngine::GameObject* gameActor, int deviceIndex);
	void InitializeSinglePlayerKeyboard(GameEngine::InputManager& input, GameEngine::GameObject* gameActor);
	void InitializeSinglePlayerController(GameEngine::InputManager& input, GameEngine::GameObject* gameActor, int deviceIndex);
	void SkipLevel();
	static void SoundCallback(int);
private:

	std::unique_ptr<GameEngine::GameObject> m_pEnvironment;
	std::unique_ptr<PengoActor> m_pPengoActor;
	std::unique_ptr<PengoActor> m_pSecondPengoActor;
	std::unique_ptr<EnemyManager> m_pEnemyManager;
	std::unique_ptr<EggObserver> m_pEggsObserver;
	std::unique_ptr<ScoreObserver> m_pScoreObserver;
	std::unique_ptr<EnvironmentObserver> m_pEnvironmentObserver;
	std::unique_ptr<GameEngine::HUD> m_pHUD;

	GameEngine::GameObject* m_pEnvironmentReference;

	static bool m_IsLevelComplete;

	int m_CurrentLevelIndex = 0;
	int m_MaxLevelsCount = 0;

	const glm::vec3 m_FirstPlayerPosition = glm::vec3{ 250,320,0 };
	glm::vec3 m_SecondPlayerPosition = glm::vec3{ 200,100,0 };

	static std::mutex m_CallbackMutex;
};




