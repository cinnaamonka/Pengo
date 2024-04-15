#pragma once
#include <BaseGame.h>
#include <Engine.h>
#include <memory>

#include <Scene.h>
#include <SceneManager.h>
#include <GameObject.h>

#include "Environment.h"
#include "PengoActor.h"

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
private:

	std::unique_ptr<GameEngine::GameObject> m_pEnvironment;
	std::unique_ptr<PengoActor> m_pPengoActor;
};



