#pragma once
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <memory>
#include <vector>
#include <SDL_scancode.h>

#include "BaseInputDevice.h"
#include "BaseCommand.h"

namespace GameEngine
{
	struct InputKeyboardBinding
	{
		SDL_Scancode key;
		InputState inputState;
	};
	

	class Keyboard final : public BaseInputDevice
	{
	public:

		Keyboard();
		~Keyboard();

        Keyboard(const Keyboard&) = delete;
        Keyboard(Keyboard&&) = delete;
        Keyboard& operator=(const Keyboard&) = delete;
        Keyboard& operator=(Keyboard&&) = delete;

		void Update() override;

		bool IsPressed(int button) override;
		bool IsReleased(int button) override;
		bool IsPrevious(int button) override;

		void HandleInput() override;
		void AddCommand(InputKeyboardBinding keyboardBinding, std::unique_ptr<BaseCommand> baseCommand);
		void RemoveCommand(InputKeyboardBinding keyboardBinding);

	private:
		// More PIMPLE concept 
		class KeyboardImpl;
		std::unique_ptr<KeyboardImpl> m_pImplPtr;

		std::vector <std::pair<InputKeyboardBinding, std::unique_ptr<BaseCommand>>> m_KeyboardCommands;


	};
}


