#pragma once
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>

#include <xinput.h>
#include <vector>
#include <memory>

#include "Singleton.h"
#include "Controller.h"
#include "BaseCommand.h"



namespace GameEngine
{
    enum class InputState : unsigned char
    {
        Pressed,
        Released,
        Previous
    };

    class InputControllerBinding
    {
    public:
        Controller::DeviceButton deviceButton;
        InputState inputState;
    };

    class InputManager final : public Singleton<InputManager>
    {
    public:
        InputManager() = default;
        ~InputManager() = default;

        InputManager(const InputManager& other) = delete;
        InputManager& operator=(const InputManager& other) = delete;
        InputManager(InputManager&& other) noexcept = delete;
        InputManager& operator=(InputManager&& other) noexcept = delete;

        bool ProcessInput();

        void AddCommand(InputControllerBinding controllerBinding, std::unique_ptr<BaseCommand> baseCommand);

        void SetController(std::unique_ptr<Controller> controller)
        {
            m_ControllerPtr = std::move(controller); 
        }

    private:
        void HandleControllerInput();
    private:
        std::unique_ptr<Controller> m_ControllerPtr;
        std::vector <std::pair<InputControllerBinding, std::unique_ptr<BaseCommand>>> m_ControllerCommands;
    };

}