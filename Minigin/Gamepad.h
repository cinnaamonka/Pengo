#pragma once
#include <memory>

namespace GameEngine
{
	class Gamepad final
	{
	public:

		explicit Gamepad(int m_ControllerIndex);
		~Gamepad();

		Gamepad(const Gamepad& other) = delete;
		Gamepad& operator=(const Gamepad& other) = delete;
		Gamepad(Gamepad&& other) noexcept = delete;
		Gamepad& operator=(Gamepad&& other) noexcept = delete;

		enum class DeviceButton : unsigned int
		{
			NONE = 0x0000,

			XINPUT_GAMEPAD_DRAD_UP = 0x0001,
			XINPUT_GAMEPAD_DRAD_DOWN = 0x0002,
			XINPUT_GAMEPAD_DRAD_LEFT = 0x0004,
			XINPUT_GAMEPAD_DRAD_RIGHT = 0x0008,

			XINPUT_GAMEPAD_START = 0x0010,
			XINPUT_GAMEPAD_BACK = 0x0020,
			XINPUT_GAMEPAD_LEFT_THUMB = 0x0040,
			XINPUT_GAMEPAD_RIGHT_THUMB = 0x0080,

			XINPUT_GAMEPAD_LEFT_SHOULDER = 0x0100,
			XINPUT_GAMEPAD_RIGHT_SHOULDER = 0x0200,

			XINPUT_GAMEPAD_A = 0x1000,
			XINPUT_GAMEPAD_B = 0x2000,
			XINPUT_GAMEPAD_X = 0x4000,
			XINPUT_GAMEPAD_Y = 0x8000
		};

		void Update();

		bool IsPressed(DeviceButton button);
		bool IsReleased(DeviceButton button);
		bool IsActive(DeviceButton button);


	private:
		// PIMPLE stuff
		class GamepadImpl;
		std::unique_ptr<GamepadImpl> m_pImplPtr;

	};

}

