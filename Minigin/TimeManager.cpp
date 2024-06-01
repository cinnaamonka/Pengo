#include "TimeManager.h"
#include <iostream>

std::chrono::duration<float> GameEngine::TimeManager::m_ElapsedTime{};
std::chrono::high_resolution_clock::time_point GameEngine::TimeManager::m_PreviousTime{ std::chrono::high_resolution_clock::now() };
std::chrono::high_resolution_clock::time_point GameEngine::TimeManager::m_CurrentTime{};
std::unordered_map<std::string, GameEngine::TimeManager::Timer> GameEngine::TimeManager::m_Timers;

float GameEngine::TimeManager::GetElapsed()
{
	return m_ElapsedTime.count();
}

std::chrono::high_resolution_clock::time_point GameEngine::TimeManager::GetCurrent()
{
	return m_CurrentTime;
}

void GameEngine::TimeManager::Update()
{
    m_CurrentTime = std::chrono::high_resolution_clock::now();
    m_ElapsedTime = std::chrono::duration<float>(m_CurrentTime - m_PreviousTime);
    m_PreviousTime = m_CurrentTime;

    for (auto it = m_Timers.begin(); it != m_Timers.end(); )
    {
        if (it->second.running && IsTimerElapsed(it->first))
        {
            it->second.running = false;
            if (it->second.callback)
            {
                it->second.callback();  
            }
            it = m_Timers.erase(it); 
        }
        else
        {
            ++it;
        }
    }
}

void GameEngine::TimeManager::StartTimer(const std::string& timerName)
{
    Timer& timer = m_Timers[timerName];
    timer.startTime = std::chrono::high_resolution_clock::now();
    timer.running = true;
}

void GameEngine::TimeManager::StopTimer(const std::string& timerName)
{
    Timer& timer = m_Timers[timerName];
    timer.endTime = GetCurrent();
    timer.running = false;
}

void GameEngine::TimeManager::StopAllTimers()
{
    for (auto& timer : m_Timers)
    {
        timer.second.running = false;
    }
}

void GameEngine::TimeManager::SetTimer(const std::string& timerName, float durationSeconds, std::function<void()> callback)
{
    Timer& timer = m_Timers[timerName];
    timer.duration = std::chrono::duration<float>(durationSeconds);
    timer.timerSet = true;
    timer.startTime = std::chrono::high_resolution_clock::now(); 
    timer.endTime = timer.startTime + std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(timer.duration);
    timer.running = true;
    timer.callback = callback;
}

bool GameEngine::TimeManager::IsTimerElapsed(const std::string& timerName)
{
    const Timer& timer = m_Timers.at(timerName);
    if (!timer.timerSet)
        return false;

    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - timer.startTime);
    return elapsedTime >= timer.duration;
}

double GameEngine::TimeManager::GetPassedTime(const std::string& timerName)
{
    const Timer& timer = m_Timers.at(timerName);

    if (timer.running)
    {
        return std::chrono::duration<double>(GetCurrent() - timer.startTime).count();
    }
    else
    {
        return std::chrono::duration<double>(timer.endTime - timer.startTime).count();
    }
}


