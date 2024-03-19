
#include <windows.h>
#include <SDL.h>
#include <../imgui-1.89.5/backends/imgui_impl_sdl2.h>

#include "InputManager.h"
#include "Controller.h"
#include "InputCommands.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#define WIN32_LEAN_AND_MEAN 
#include <xinput.h>

namespace GameEngine
{
	bool GameEngine::InputManager::ProcessInput()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				return false;
			}
			if (e.type == SDL_KEYDOWN)
			{

			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{

			}

			ImGui_ImplSDL2_ProcessEvent(&e);
		}

		for (const auto& devicePtr : m_DevicesPtr)
		{
			devicePtr->Update();
			devicePtr->HandleInput();
		}

		return true;
	}
}
