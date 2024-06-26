#pragma once
#include <chrono>
#include "Singleton.h"
#include <unordered_map>
#include <functional>

namespace GameEngine
{
    class TimeManager final : public GameEngine::Singleton<TimeManager>
    {
    public:
       
        static float GetElapsed();
        static std::chrono::high_resolution_clock::time_point GetCurrent();
        static void Update();
        static void StartTimer(const std::string& timerName);
        static void StopTimer(const std::string& timerName);
        static void StopAllTimers();
        static void SetTimer(const std::string& timerName, float durationSeconds, std::function<void()> callback = nullptr);
        static bool IsTimerElapsed(const std::string& timerName);
        static double GetPassedTime(const std::string& timerName);

    private:
        friend class GameEngine::Singleton<TimeManager>;
        TimeManager() = default;

        static std::chrono::duration<float> m_ElapsedTime;
        static std::chrono::high_resolution_clock::time_point m_PreviousTime;
        static std::chrono::high_resolution_clock::time_point m_CurrentTime;

        struct Timer
        {
            std::chrono::high_resolution_clock::time_point startTime{};
            std::chrono::high_resolution_clock::time_point endTime{};
            std::chrono::duration<float> duration{};
            bool running{ false };
            bool timerSet{ false };
            std::function<void()> callback{ nullptr };
        };

        static std::unordered_map<std::string, Timer> m_Timers;
    };
}


