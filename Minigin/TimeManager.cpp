#include "TimeManager.h"

duration<float> GameEngine::Time::m_ElapsedTime{};
std::chrono::high_resolution_clock::time_point GameEngine::Time::m_PreviousTime{ std::chrono::high_resolution_clock::now() };
std::chrono::high_resolution_clock::time_point GameEngine::Time::m_CurrentTime{};

float GameEngine::Time::GetElapsed()
{
    return m_ElapsedTime.count();
}

high_resolution_clock::time_point GameEngine::Time::GetCurrent()
{
    return m_CurrentTime;
}

void GameEngine::Time::Update()
{
    m_CurrentTime = high_resolution_clock::now();
    m_ElapsedTime = duration<float>(m_CurrentTime - m_PreviousTime);
    m_PreviousTime = m_CurrentTime;
}
