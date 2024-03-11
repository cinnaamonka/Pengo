#pragma once
#include <xinput.h>

#include "Singleton.h"

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>

namespace GameEngine
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		XINPUT_STATE m_CurrentState;
	};

}
