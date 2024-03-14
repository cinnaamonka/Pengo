#pragma once
#include <Windows.h>
#include <Xinput.h>

#include <memory>

namespace GameEngine
{
	class Controller final
	{
	public:

		explicit Controller(int m_ControllerIndex);
		~Controller();

		Controller(const Controller& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller(Controller&& other) noexcept = delete;
		Controller& operator=(Controller&& other) noexcept = delete;

		enum class DeviceButton : unsigned int
		{
			NONE = 0x0000,

			XINPUT_GAMEPAD_DRAD_UP = 0x0001,
			XINPUT_GAMEPAD_DRAD_DOWN = 0x0002,
			XINPUT_GAMEPAD_DRAD_LEFT = 0x0004,
			XINPUT_GAMEPAD_DRAD_RIGHT = 0x0008
		};

		void Update();

		bool IsPressed(DeviceButton button);
		bool IsReleased(DeviceButton button);
		bool IsPrevious(DeviceButton button);

	private:
		// PIMPLE stuff
		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_pImplPtr;

	};

}

