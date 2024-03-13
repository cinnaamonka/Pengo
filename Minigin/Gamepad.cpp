#include "Gamepad.h"

#include <windows.h>
#include <Xinput.h>
namespace GameEngine
{
	// use PIMPLE pattern not sure if correct, probably refactor
	class Gamepad::GamepadImpl final
	{
		int m_ControllerIndex;

		XINPUT_STATE m_InputState{};

		unsigned int m_ButtonsPressedThisFrame;
		unsigned int m_ButtonsReleasedThisFrame;
		unsigned int m_ButtonsActiveThisFrame;

	public:
		GamepadImpl(int m_ControllerIndex)
			: m_ControllerIndex{ m_ControllerIndex }, 
			m_ButtonsPressedThisFrame(0),
			m_ButtonsReleasedThisFrame(0),
			m_ButtonsActiveThisFrame(0)
		{
		}

		void UpdateGamepad()
		{
			XINPUT_STATE currentState{};
			ZeroMemory(&currentState, sizeof(XINPUT_STATE));
			DWORD dwResult = XInputGetState(m_ControllerIndex, &currentState);

			if (dwResult != ERROR_SUCCESS)
			{
				ZeroMemory(&m_InputState, sizeof(XINPUT_STATE));
				m_ButtonsActiveThisFrame = 0;
				m_ButtonsPressedThisFrame = 0;
				m_ButtonsReleasedThisFrame = 0;
				return;
			}

			const unsigned int buttonChanges = currentState.Gamepad.wButtons ^ m_ButtonsActiveThisFrame;
			m_ButtonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
			m_ButtonsReleasedThisFrame = buttonChanges & m_ButtonsActiveThisFrame;
			m_ButtonsActiveThisFrame = currentState.Gamepad.wButtons;

			CopyMemory(&m_InputState, &currentState, sizeof(XINPUT_STATE));
		}

		bool IsPressed(unsigned int button) const
		{
			return m_ButtonsPressedThisFrame & button;
		}

		bool IsReleased(unsigned int button) const
		{
			return m_ButtonsReleasedThisFrame & button;
		}
		bool IsActive(unsigned int button) const
		{
			return m_ButtonsActiveThisFrame & button;
		}
	};
	GameEngine::Gamepad::Gamepad(int m_ControllerIndex)
	{
		m_pImplPtr = std::make_unique<GamepadImpl>(m_ControllerIndex);
	}

	GameEngine::Gamepad::~Gamepad()
	{
	}

	void GameEngine::Gamepad::Update()
	{
		m_pImplPtr->UpdateGamepad();
	}

	bool GameEngine::Gamepad::IsPressed(DeviceButton button)
	{
		return m_pImplPtr->IsPressed(static_cast<unsigned int>(button));
	}

	bool GameEngine::Gamepad::IsReleased(DeviceButton button)
	{
		return m_pImplPtr->IsReleased(static_cast<unsigned int>(button));
	}

	bool GameEngine::Gamepad::IsActive(DeviceButton button)
	{
		return m_pImplPtr->IsActive(static_cast<unsigned int>(button));
	}
}
