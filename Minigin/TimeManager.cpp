#include "TimeManager.h"

std::chrono::duration<float> GameEngine::TimeManager::m_ElapsedTime{};
std::chrono::high_resolution_clock::time_point GameEngine::TimeManager::m_PreviousTime{ std::chrono::high_resolution_clock::now() };
std::chrono::high_resolution_clock::time_point GameEngine::TimeManager::m_CurrentTime{};
std::chrono::time_point<std::chrono::high_resolution_clock> GameEngine::TimeManager::m_StartTime;
std::chrono::time_point<std::chrono::high_resolution_clock> GameEngine::TimeManager::m_EndTime;
bool GameEngine::TimeManager::m_TimerSet = false;
std::chrono::duration<float> GameEngine::TimeManager::m_Duration = std::chrono::duration<float>(0);
bool GameEngine::TimeManager::m_Running = false;

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

void GameEngine::TimeManager::StartTimer()
{
    m_StartTime = std::chrono::high_resolution_clock::now(); 
    m_Running = true; 
}

void GameEngine::TimeManager::StopTimer()
{
    m_EndTime = std::chrono::high_resolution_clock::now();
    m_Running = false;
}

void GameEngine::TimeManager::SetTimer(float durationSeconds)
{
    m_Duration = std::chrono::duration<float>(durationSeconds);
    m_StartTime = std::chrono::high_resolution_clock::now();
    m_TimerSet = true;
    m_Running = true;
}

bool GameEngine::TimeManager::IsTimerElapsed()
{
    if (!m_TimerSet)
    {
        return false;
    }

    auto currentTime = std::chrono::high_resolution_clock::now();
    if ((currentTime - m_StartTime) >= m_Duration)
    {
        m_Running = false;
        m_TimerSet = false;
        return true;
    }

    return false;
}

double GameEngine::TimeManager::GetPassedTime()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime; 

    if (m_Running) 
    { 
        endTime = std::chrono::high_resolution_clock::now(); 
    }
    else
    {
        endTime = m_EndTime; 
    }

    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count() / 1000.0; 
}

