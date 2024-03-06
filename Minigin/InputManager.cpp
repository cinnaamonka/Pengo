#include "../pch.h"
#include "InputManager.h"
#include "../backends/imgui_impl_sdl.h"
#include <xinput.h>

bool GameEngine::InputManager::ProcessInput()
{
	/*ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);*/
	
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
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}

		ImGui_ImplSDL2_ProcessEvent(&e);
		// etc...
	}

	return true;
}
