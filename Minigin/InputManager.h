#pragma once
#include "Singleton.h"

namespace GameEngine
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
	};

}
