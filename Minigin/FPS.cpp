#include "FPS.h"
#include "Time.h"
#include <numeric>

GameEngine::FPS::FPS(GameObject* GOptr) : Component(GOptr), m_FPSCollection(0.0), m_AverageFramesAmount(200), m_AverageFPS(0)
{}


void GameEngine::FPS::Update()
{
	double fps = 1 / GameEngine::Time::GetElapsed();

	m_FPSCollection.push_front(fps);

	// renew the fps collection
	if (m_FPSCollection.size() > m_AverageFramesAmount)
	{
		m_FPSCollection.pop_back();
	}
	// get average fps
	m_AverageFPS = std::accumulate(m_FPSCollection.begin(), m_FPSCollection.end(), 0.0) / m_FPSCollection.size();

}