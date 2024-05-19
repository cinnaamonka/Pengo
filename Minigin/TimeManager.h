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
		static void StartTimer();
		static void StopTimer();
		static void SetTimer(float durationSeconds);
		static bool IsTimerElapsed(); 
		static double GetPassedTime(); 
	private:
		friend class GameEngine::Singleton<TimeManager>;
		TimeManager() = default;
		static  std::chrono::duration<float> m_ElapsedTime;
		static  std::chrono::high_resolution_clock::time_point m_PreviousTime;
		static  std::chrono::high_resolution_clock::time_point m_CurrentTime;

		static std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
		static std::chrono::time_point<std::chrono::high_resolution_clock> m_EndTime;
		static bool m_Running;
		static bool m_TimerSet;
		static std::chrono::duration<float> m_Duration; 
	};
}


