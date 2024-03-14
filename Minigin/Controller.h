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

		/*	XINPUT_GAMEPAD_LEFT_THUMB_UP = 0x0010,
			XINPUT_GAMEPAD_LEFT_THUMB_DOWN = 0x0020, 
			XINPUT_GAMEPAD_LEFT_THUMB_LEFT = 0x0040, 
			XINPUT_GAMEPAD_LEFT_THUMB_RIGHT = 0x0080,

			XINPUT_GAMEPAD_RIGHT_THUMB_UP = 0x0100,
			XINPUT_GAMEPAD_RIGHT_THUMB_DOWN = 0x0200,
			XINPUT_GAMEPAD_RIGHT_THUMB_LEFT = 0x0400,
			XINPUT_GAMEPAD_RIGHT_THUMB_RIGHT = 0x0800,*/

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

