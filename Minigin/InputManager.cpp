
#include <windows.h>
#include <SDL.h>
#include <../imgui-1.89.5/backends/imgui_impl_sdl2.h>

#include "InputManager.h"
#include "Controller.h"
#include "MoveCommand.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#define WIN32_LEAN_AND_MEAN 
#include <xinput.h>


bool GameEngine::InputManager::ProcessInput()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            return false;
        }
        if (e.type == SDL_KEYDOWN)
        {

        }
        if (e.type == SDL_MOUSEBUTTONDOWN) 
        {

        }

        ImGui_ImplSDL2_ProcessEvent(&e);
    }

    m_ControllerPtr->Update();
    m_KeyboardPtr->Update();

    HandleControllerInput();
    HandleKeyboardInput();


    return true;
}

void GameEngine::InputManager::AddControllerCommand(InputControllerBinding controllerBinding, std::unique_ptr<BaseCommand> baseCommand)
{
    if (baseCommand != nullptr)
    {
        m_ControllerCommands.push_back(std::pair<InputControllerBinding, std::unique_ptr<BaseCommand>>{ controllerBinding, std::move(baseCommand) });
    }
}

void GameEngine::InputManager::AddKeyboardCommand(InputKeyboardBinding keyboardBinding, std::unique_ptr<BaseCommand> baseCommand)
{
    if (baseCommand != nullptr)
    {
        m_KeyboardCommands.push_back(std::pair<InputKeyboardBinding, std::unique_ptr<BaseCommand>>{ keyboardBinding, std::move(baseCommand) });
    }
}

void GameEngine::InputManager::HandleControllerInput()
{
    for (const auto& controllerInput : m_ControllerCommands)
    {
        switch (controllerInput.first.inputState)
        {
        case InputState::Previous:
        {
            if (m_ControllerPtr->IsPrevious(controllerInput.first.deviceButton))
            {
                controllerInput.second->Execute();
            }

            break;
        }
        case InputState::Pressed: 
        {
            if (m_ControllerPtr->IsPressed(controllerInput.first.deviceButton))
            {
                controllerInput.second->Execute();
            }

            break;
        }
        case InputState::Released: 
        {
            if (m_ControllerPtr->IsReleased(controllerInput.first.deviceButton))
            {
                controllerInput.second->Execute();
            }
            break;
        }
        }
    }
}

void GameEngine::InputManager::HandleKeyboardInput()
{
    for (const auto& keyboardInput : m_KeyboardCommands)
    {
        switch (keyboardInput.first.inputState)
        {
        case InputState::Previous:
        {
            if (m_KeyboardPtr->IsPrevious(keyboardInput.first.key))
            {
                keyboardInput.second->Execute();
            }

            break;
        }
        case InputState::Pressed:
        {
            if (m_KeyboardPtr->IsPressed(keyboardInput.first.key))
            {
                keyboardInput.second->Execute();
            }

            break;
        }
        case InputState::Released:
        {
            if (m_KeyboardPtr->IsReleased(keyboardInput.first.key))
            {
                keyboardInput.second->Execute();
            }
            break;
        }
        }
    }
}
