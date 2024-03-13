#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <../imgui-1.89.5/backends/imgui_impl_sdl2.h>

#include "InputManager.h"
#include "Controller.h"
#include "MoveCommand.h"
#define IMGUI_DEFINE_MATH_OPERATORS
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

    HandleControllerInput();

    return true;
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
        }
        case InputState::Pressed: 
        {
            if (m_ControllerPtr->IsPressed(controllerInput.first.deviceButton))
            {
                controllerInput.second->Execute();
            }
        }
        case InputState::Released: 
        {
            if (m_ControllerPtr->IsReleased(controllerInput.first.deviceButton))
            {
                controllerInput.second->Execute();
            }
        }
        }
    }
}