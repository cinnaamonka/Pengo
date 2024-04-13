#include "TimeManager.h"

std::chrono::duration<float> GameEngine::TimeManager::m_ElapsedTime{};
std::chrono::high_resolution_clock::time_point GameEngine::TimeManager::m_PreviousTime{ std::chrono::high_resolution_clock::now() };
std::chrono::high_resolution_clock::time_point GameEngine::TimeManager::m_CurrentTime{};

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
    m_CurrentTime =  std::chrono::high_resolution_clock::now();
    m_ElapsedTime =  std::chrono::duration<float>(m_CurrentTime - m_PreviousTime);
    m_PreviousTime = m_CurrentTime;
}
