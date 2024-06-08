
#include <windows.h>
#include <SDL.h>
#include <../imgui/backends/imgui_impl_sdl2.h>

#include "InputManager.h"
#include "Controller.h"

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

		for (int i = 0; i < static_cast<int>(m_pDevices.size()); ++i)
		{
			m_pDevices[i]->Update();
			m_pDevices[i]->HandleInput();
		}

		return true;
	}
}
