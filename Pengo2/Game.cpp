#include "Game.h"

#include "InputManager.h"
#include "InputCommands.h"

#include <TransformComponent.h>
#include <TextureComponent.h>
#include <RenderComponent.h>

#include <Scene.h>
#include <SceneManager.h>
#include <GameObject.h>

#include <memory>

void Game::Initialize()
{
    auto& scene = GameEngine::SceneManager::GetInstance().CreateScene("Demo");

    auto characterPengo = std::make_unique<GameEngine::GameObject>();
    characterPengo->AddComponent<GameEngine::TransformComponent>(glm::vec3(300, 350, 0));
    characterPengo->AddComponent<GameEngine::TextureComponent>("Pengo.tga");
    characterPengo->AddComponent<GameEngine::RenderComponent>();
    GameEngine::GameObject* referenceToCharacterPengo = characterPengo.get();
    scene.Add(std::move(characterPengo));

    InitializeInputSystem(referenceToCharacterPengo);
    m_pEnvironment = std::make_unique<Environment>("Level.json",&scene); 
}

void Game::InitializeInputSystem(GameEngine::GameObject* gameActor)
{
    auto& input = GameEngine::InputManager::GetInstance(); 
    auto m_Controller = std::make_unique<GameEngine::Controller>(0); 
    auto m_Keyboard = std::make_unique<GameEngine::Keyboard>(); 
    input.AddDevice(std::move(m_Controller));
    input.AddDevice(std::move(m_Keyboard));

    input.AddCommand<GameEngine::Controller>(
        GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_LEFT, GameEngine::InputState::Previous },
        std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ -1, 0, 0 }, 30.0f));

    input.AddCommand<GameEngine::Controller>(
        GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_RIGHT, GameEngine::InputState::Previous },
        std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 1, 0, 0 }, 30.0f));

    input.AddCommand<GameEngine::Controller>(
        GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_UP, GameEngine::InputState::Previous },
        std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 0, -1, 0 }, 30.0f));

    input.AddCommand<GameEngine::Controller>(
        GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_DOWN, GameEngine::InputState::Previous },
        std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 0, 1, 0 }, 30.0f));

    //Keyboard Input
    input.AddCommand<GameEngine::Keyboard>(
        GameEngine::InputKeyboardBinding{ SDL_SCANCODE_A, GameEngine::InputState::Previous },
        std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ -1,0, 0 }, 30.0f));

    input.AddCommand<GameEngine::Keyboard>(
        GameEngine::InputKeyboardBinding{ SDL_SCANCODE_D, GameEngine::InputState::Previous },
        std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 1,0, 0 }, 30.0f));

    input.AddCommand<GameEngine::Keyboard>(
        GameEngine::InputKeyboardBinding{ SDL_SCANCODE_W, GameEngine::InputState::Previous },
        std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 0,-1, 0 }, 30.0f));

    input.AddCommand<GameEngine::Keyboard>(
        GameEngine::InputKeyboardBinding{ SDL_SCANCODE_S, GameEngine::InputState::Previous },
        std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 0,1, 0 }, 30.0f));
}