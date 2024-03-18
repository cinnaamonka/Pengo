#include "Controller.h"

namespace GameEngine
{
	// use PIMPLE pattern not sure if correct, probably refactor
	class Controller::ControllerImpl final
	{
		int m_ControllerIndex;

		XINPUT_STATE m_InputState{};

		unsigned int m_ButtonsPressedThisFrame;
		unsigned int m_ButtonsReleasedThisFrame;
		unsigned int m_PreviousButtonsThisFrame;

	public:
		ControllerImpl(int m_ControllerIndex)
			: m_ControllerIndex{ m_ControllerIndex },
			m_ButtonsPressedThisFrame(0),
			m_ButtonsReleasedThisFrame(0),
			m_PreviousButtonsThisFrame(0)
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
				m_PreviousButtonsThisFrame = 0;
				m_ButtonsPressedThisFrame = 0;
				m_ButtonsReleasedThisFrame = 0;
				return;
			}

			const unsigned int buttonChanges = currentState.Gamepad.wButtons ^ m_PreviousButtonsThisFrame;
			m_ButtonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
			m_ButtonsReleasedThisFrame = buttonChanges & m_PreviousButtonsThisFrame;
			m_PreviousButtonsThisFrame = currentState.Gamepad.wButtons;

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
			return m_PreviousButtonsThisFrame & button;
		}
	};
	GameEngine::Controller::Controller(int m_ControllerIndex)
	{
		m_pImplPtr = std::make_unique<ControllerImpl>(m_ControllerIndex);
	}

	GameEngine::Controller::~Controller()
	{
	}

	void GameEngine::Controller::Update()
	{
		if (m_pImplPtr)
		{
			m_pImplPtr->UpdateGamepad();
		}
	}

	bool GameEngine::Controller::IsPressed(int button)
	{
		return m_pImplPtr->IsPressed(static_cast<unsigned int>(button));
	}

	bool GameEngine::Controller::IsReleased(int button)
	{
		return m_pImplPtr->IsReleased(static_cast<unsigned int>(button));
	}

	bool GameEngine::Controller::IsPrevious(int button)
	{
		return m_pImplPtr->IsActive(static_cast<unsigned int>(button));
	}
	void Controller::HandleInput()
	{
		for (const auto& controllerInput : m_ControllerCommands)
		{
			switch (controllerInput.first.inputState)
			{
			case InputState::Previous:
			{
				if (this->IsPrevious(static_cast<int>(controllerInput.first.deviceButton)))
				{
					controllerInput.second->Execute();
				}

				break;
			}
			case InputState::Pressed:
			{
				if (this->IsPressed(static_cast<int>(controllerInput.first.deviceButton)))
				{
					controllerInput.second->Execute();
				}

				break;
			}
			case InputState::Released:
			{
				if (this->IsReleased(static_cast<int>(controllerInput.first.deviceButton)))
				{
					controllerInput.second->Execute();
				}
				break;
			}
			}
		}
	}
	void Controller::AddCommand(InputControllerBinding binding, std::unique_ptr<BaseCommand> command)
	{
		m_ControllerCommands.push_back(std::pair<InputControllerBinding, std::unique_ptr<BaseCommand>>{ binding, std::move(command) });
	}
}
