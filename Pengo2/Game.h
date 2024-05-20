#pragma once
#include <BaseGame.h>
#include <Engine.h>
#include <memory>

#include <Scene.h>
#include <SceneManager.h>
#include <GameObject.h>

#include "Environment.h"
#include "PengoActor.h"
#include "EnemyActor.h"
#include "EggObserver.h"
#include "EnemyManager.h"
#include "EnvironmentObserver.h"
#include "ScoreObserver.h"
#include <HUD.h>

class Game final :public GameEngine::BaseGame
{
public:
	Game() = default;
	~Game() override {};

	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) noexcept = delete;
	Game& operator=(Game&& other) noexcept = delete;

	void Initialize();

private:
	void InitializeInputSystem(GameEngine::GameObject* gameActor) override;
	void LoadSounds();
private:

	std::unique_ptr<GameEngine::GameObject> m_pEnvironment;
	std::unique_ptr<PengoActor> m_pPengoActor;
	std::unique_ptr<EnemyManager> m_pEnemyManager;
	std::unique_ptr<EggObserver> m_pEggsObserver;
	std::unique_ptr<ScoreObserver> m_pScoreObserver;
	std::unique_ptr<EnvironmentObserver> m_pEnvironmentObserver;
	std::unique_ptr<GameEngine::HUD> m_pHUD;

	GameEngine::GameObject* m_pEnvironmentReference;

	std::vector<glm::vec3> m_EnemiesPositions;

	bool m_IspLaying = true;
};




