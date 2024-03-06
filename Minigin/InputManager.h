#pragma once
#include <xinput.h>

namespace GameEngine
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		XINPUT_STATE m_CurrentState;
	};

}
