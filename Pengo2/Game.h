#pragma once
#include <BaseGame.h>
#include <Engine.h>
#include <memory>

#include <Scene.h>
#include <SceneManager.h>
#include <GameObject.h>
#include <StatesAndTransitions.h>

#include "Environment.h"

class Game final :public GameEngine::BaseGame
{
public:
	Game() = default;
	~Game() = default;

	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) noexcept = delete;
	Game& operator=(Game&& other) noexcept = delete;

	void Initialize();

private:
	void InitializeInputSystem(GameEngine::GameObject* gameActor) override;
private:

	std::unique_ptr<GameEngine::GameObject> m_pEnvironment;
	std::unique_ptr<GameEngine::GameObject> m_pActor;
	GameEngine::Blackboard* m_pBlackboard;

	GameEngine::IdleState* m_IdleState;
	GameEngine::RunningState* m_RunningState;

	GameEngine::IsInputGiven* m_IsInputGiven;
	GameEngine::IsInputNotGiven* m_IsNotInputGiven;
};




