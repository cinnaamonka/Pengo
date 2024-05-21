#include "TimeManager.h"

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
}

void GameEngine::TimeManager::StartTimer(const std::string& timerName)
{
	Timer& timer = m_Timers[timerName];
	timer.startTime = GetCurrent();
	timer.running = true;
}

void GameEngine::TimeManager::StopTimer(const std::string& timerName)
{
	Timer& timer = m_Timers[timerName];
	timer.endTime = GetCurrent();
	timer.running = false;
}

void GameEngine::TimeManager::SetTimer(const std::string& timerName, float durationSeconds)
{
	Timer& timer = m_Timers[timerName];
	timer.duration = std::chrono::duration<float>(durationSeconds);
	timer.timerSet = true;
	timer.startTime = GetCurrent();
    timer.endTime = timer.startTime + std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(timer.duration); 
	timer.running = true;
}

bool GameEngine::TimeManager::IsTimerElapsed(const std::string& timerName)
{
    const Timer& timer = m_Timers.at(timerName);
    if (!timer.timerSet)
        return false;

    if (timer.running)
    {
        return GetCurrent() >= timer.endTime;
    }
    else
    {
        return timer.endTime <= timer.startTime + timer.duration;
    }
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


