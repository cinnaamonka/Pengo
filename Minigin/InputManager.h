#pragma once
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>

#include <xinput.h>
#include <vector>
#include <memory>

#include "Singleton.h"
#include "Controller.h"
#include "Keyboard.h"
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

    struct InputKeyboardBinding
    {
        SDL_Scancode key;
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

        void AddControllerCommand(InputControllerBinding controllerBinding, std::unique_ptr<BaseCommand> baseCommand);
        void AddKeyboardCommand(InputKeyboardBinding keyboardBinding, std::unique_ptr<BaseCommand> baseCommand);

        void SetController(std::unique_ptr<Controller> controller)
        {
            m_ControllerPtr = std::move(controller); 
        }

        void SetKeyboard(std::unique_ptr<Keyboard> keyboard)
        {
            m_KeyboardPtr = std::move(keyboard);
        }

    private:
        void HandleControllerInput();
        void HandleKeyboardInput();
    private:
        std::unique_ptr<Controller> m_ControllerPtr;
        std::vector <std::pair<InputControllerBinding, std::unique_ptr<BaseCommand>>> m_ControllerCommands;

        std::unique_ptr<Keyboard> m_KeyboardPtr;
        std::vector <std::pair<InputKeyboardBinding, std::unique_ptr<BaseCommand>>> m_KeyboardCommands;
    };

}