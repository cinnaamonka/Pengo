#include "Keyboard.h"
#include "BaseCommand.h"

#include <SDL.h>
#include <vector>
#include <algorithm>
#include <functional>

namespace GameEngine
{
	class Keyboard::KeyboardImpl final
	{
		std::vector<Uint8> m_PreviousButton;
		std::vector<Uint8> m_PressedButton;
		std::vector<Uint8> m_ReleasedButton;

	public:
		KeyboardImpl()
		{
			int nrKeys{};
			SDL_GetKeyboardState(&nrKeys);
			m_PreviousButton.resize(nrKeys);
			m_PressedButton.resize(nrKeys);
			m_ReleasedButton.resize(nrKeys);
		}

		void Update()
		{
			int keysCount = 0;
			auto keyboardState = SDL_GetKeyboardState(&keysCount);
			std::vector<Uint8> currentUsedButton(keyboardState, keyboardState + keysCount);

			std::vector<Uint8> keyChanges(currentUsedButton.size());
			std::transform(currentUsedButton.begin(), currentUsedButton.end(), m_PreviousButton.begin(), keyChanges.begin(), std::bit_xor<Uint8>());
			std::transform(keyChanges.begin(), keyChanges.end(), currentUsedButton.begin(), m_PressedButton.begin(), std::bit_and<Uint8>());
			std::transform(keyChanges.begin(), keyChanges.end(), m_PreviousButton.begin(), m_ReleasedButton.begin(), std::bit_and<Uint8>());
			m_PreviousButton = std::move(currentUsedButton);
		}

		bool IsPressed(unsigned int button) const
		{
			return m_PressedButton[button];
		};

		bool IsReleased(unsigned int button) const
		{
			return m_ReleasedButton[button];
		}

		bool IsPrevious(unsigned int button) const 
		{
			return m_PreviousButton[button];
		}
	};

	Keyboard::Keyboard()
	{
		m_pImplPtr = std::make_unique<KeyboardImpl>();
	}

	Keyboard::~Keyboard()
	{

	}

	void Keyboard::Update()
	{
		return m_pImplPtr->Update();
	}

	bool Keyboard::IsPressed(int button)
	{
		return m_pImplPtr->IsPressed(button);
	}

	bool Keyboard::IsReleased(int button)
	{
		return m_pImplPtr->IsReleased(button);
	}

	bool Keyboard::IsPrevious(int button)
	{
		return m_pImplPtr->IsPrevious(button);
	}

	void Keyboard::HandleInput()
	{
		for (const auto& keyboardInput : m_KeyboardCommands)
		{
			switch (keyboardInput.first.inputState)
			{
			case InputState::Previous:
			{
				if (this->IsPrevious(keyboardInput.first.key))
				{
					keyboardInput.second->Execute();
				}

				break;
			}
			case InputState::Pressed:
			{
				if (this->IsPressed(keyboardInput.first.key))
				{
					keyboardInput.second->Execute();
				}

				break;
			}
			case InputState::Released:
			{
				if (this->IsReleased(keyboardInput.first.key))
				{
					keyboardInput.second->Execute();
				}
				break;
			}
			}
		}
	}

	void Keyboard::AddCommand(InputKeyboardBinding keyboardBinding, std::unique_ptr<BaseCommand> baseCommand)
	{
		if (baseCommand != nullptr)
		{
			m_KeyboardCommands.push_back(std::pair<InputKeyboardBinding, std::unique_ptr<BaseCommand>>{ keyboardBinding, std::move(baseCommand) });
		}
	}

}
