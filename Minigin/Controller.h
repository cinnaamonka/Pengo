#pragma once
#include <Windows.h>
#include <Xinput.h>

#include <memory>
#include <vector>

#include "BaseInputDevice.h"
#include "BaseCommand.h"

namespace GameEngine
{
	
	enum class DeviceButton : unsigned int
	{
		NONE = 0x0000,

		XINPUT_CONTROLLER_A = 0x1000,
		XINPUT_CONTROLLER_B = 0x2000,
		XINPUT_CONTROLLER_X = 0x4000,
		XINPUT_CONTROLLER_Y = 0x8000,

		XINPUT_GAMEPAD_DRAD_UP = 0x0001,
		XINPUT_GAMEPAD_DRAD_DOWN = 0x0002,
		XINPUT_GAMEPAD_DRAD_LEFT = 0x0004,
		XINPUT_GAMEPAD_DRAD_RIGHT = 0x0008
	};

	class InputControllerBinding
	{
	public:
		DeviceButton deviceButton;
		InputState inputState;
		int index = 0;
	};

	class Controller final : public BaseInputDevice
	{
	public:

		explicit Controller(int m_ControllerIndex);
		~Controller();

		Controller(const Controller& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller(Controller&& other) noexcept = delete;
		Controller& operator=(Controller&& other) noexcept = delete;

		void Update() override;

		bool IsPressed(int button) override;
		bool IsReleased(int button) override;
		bool IsPrevious(int button) override;
		int GetIndex() const override;
		 
		void HandleInput() override;

		void AddCommand(InputControllerBinding binding, std::unique_ptr<BaseCommand> command);
		void RemoveCommand(InputControllerBinding binding);

	private:
		// PIMPLE stuff
		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_pImplPtr;

		std::vector<std::pair<InputControllerBinding, std::unique_ptr<BaseCommand>>> m_ControllerCommands;
	};

}

