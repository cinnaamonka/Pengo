#pragma once
#include "Singleton.h"
#include <chrono>

using namespace std::chrono;

namespace GameEngine
{
	class Time final : public GameEngine::Singleton<Time>
	{
	public:
		static float GetElapsed();
		static high_resolution_clock::time_point GetCurrent();
		static void Update();
	private:
		friend class GameEngine::Singleton<Time>;
		Time() = default;
		static duration<float> m_ElapsedTime;
		static high_resolution_clock::time_point m_PreviousTime;
		static high_resolution_clock::time_point m_CurrentTime;
	};
}


