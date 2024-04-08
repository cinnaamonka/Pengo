#include "FPS.h"
#include "TimeManager.h"
#include "TextComponent.h"

#include <numeric>

GameEngine::FPS::FPS(GameObject* GOptr):
	BaseComponent(GOptr), 
	m_FPSCollection{},
	m_AverageFramesAmount(200),
	m_AverageFPS(0),
	m_TextComponent(nullptr)
{
	m_TextComponent = GetGameObject()->GetComponent<TextComponent>();
}

void GameEngine::FPS::Update()
{
	double fps = 1 / GameEngine::Time::GetElapsed();

	m_FPSCollection.push_front(fps);

	// renew the fps collection
	if (static_cast<int>(m_FPSCollection.size()) > m_AverageFramesAmount)
	{
		m_FPSCollection.pop_back();
	}
	// get average fps
	m_AverageFPS = std::accumulate(m_FPSCollection.begin(), m_FPSCollection.end(), 0.0) / m_FPSCollection.size();

	if (m_TextComponent != nullptr)
	{
		m_TextComponent->SetText(std::format("{:.1f}", m_AverageFPS) + "FPS");

	}
	
}