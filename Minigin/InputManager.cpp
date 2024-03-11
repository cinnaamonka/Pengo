#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <../imgui-1.89.5/backends/imgui_impl_sdl2.h>

#include "InputManager.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <xinput.h>

bool GameEngine::InputManager::ProcessInput()
{
	//TODO: ASK WTF
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
	}

	return true;
}
