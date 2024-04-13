#pragma once
#include <chrono>
#include "Singleton.h"


namespace GameEngine
{
	class TimeManager final : public GameEngine::Singleton<TimeManager>
	{
	public:
		static float GetElapsed();
		static  std::chrono::high_resolution_clock::time_point GetCurrent();
		static void Update();
	private:
		friend class GameEngine::Singleton<TimeManager>;
		TimeManager() = default;
		static  std::chrono::duration<float> m_ElapsedTime;
		static  std::chrono::high_resolution_clock::time_point m_PreviousTime;
		static  std::chrono::high_resolution_clock::time_point m_CurrentTime;
	};
}


