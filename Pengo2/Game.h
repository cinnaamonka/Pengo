#pragma once
#include <BaseGame.h>
#include <Engine.h>
#include <memory>

#include <TransformComponent.h>
#include <TextureComponent.h>
#include <RenderComponent.h>

#include <Scene.h>
#include <SceneManager.h>
#include <GameObject.h>

#include "Environment.h"

class GameObject;
class Environment;

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

	std::unique_ptr<Environment> m_pEnvironment;
};




