#pragma once
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <memory>
#include <SDL_scancode.h>

namespace GameEngine
{
	class Keyboard
	{
	public:

		Keyboard();
		~Keyboard();

        Keyboard(const Keyboard&) = delete;
        Keyboard(Keyboard&&) = delete;
        Keyboard& operator=(const Keyboard&) = delete;
        Keyboard& operator=(Keyboard&&) = delete;

		void Update();

		bool IsPressed(SDL_Scancode button);
		bool IsReleased(SDL_Scancode button);
		bool IsPrevious(SDL_Scancode button);

	private:
		// More PIMPLE concept 
		class KeyboardImpl;
		std::unique_ptr<KeyboardImpl> m_pImplPtr;

	};
}


