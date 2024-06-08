#include "EggObserver.h"
#include <TransformComponent.h>
#include <TextureComponent.h>
#include <RenderComponent.h>
#include <GameObject.h>
#include <FSM.h>
#include <AnimationComponent.h>
#include <Texture2D.h>


EggObserver::EggObserver(GameEngine::Scene* pScene)
{
	m_pScene = pScene;
}


void EggObserver::Notify(const glm::vec3& message_from_subject)
{
	if (m_pBreakingEggState)
	{
		m_pBreakingEggState.release();
	}
	if (m_pIsEggBroken)
	{
		m_pIsEggBroken.release();
	}
	if (m_pBrokenEggState)
	{
		m_pBrokenEggState.release();
	}
	if (m_pWaitingEggState)
	{
		m_pWaitingEggState.release();
	}
	if (m_pIsEggAnimationWaiting)
	{
		m_pIsEggAnimationWaiting.release();
	}

	auto gameObject = std::make_unique<GameEngine::GameObject>();

	gameObject->AddComponent<GameEngine::TransformComponent>(message_from_subject);
	gameObject->AddComponent<GameEngine::TextureComponent>("Egg.tga", m_HorizontalAmountOfFrames);
	gameObject->AddComponent<GameEngine::AnimationComponent>();
	gameObject->AddComponent<GameEngine::RenderComponent>();
	
	auto textureSizeX = gameObject->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().x / m_HorizontalAmountOfFrames;
	auto textureSizeY = gameObject->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().y;

	gameObject->GetComponent<GameEngine::TransformComponent>()->SetDimensions({ 0, 0,textureSizeX,textureSizeY });

	if (!m_pBreakingEggState)
	{
		m_pBreakingEggState = std::make_unique<BreakingEggState>();
		m_pIsEggBroken = std::make_unique<IsEggBroken>();
		m_pBrokenEggState = std::make_unique<BrokenEggState>();
		m_pWaitingEggState = std::make_unique<WaitingState>();
		m_pIsEggAnimationWaiting = std::make_unique<IsWaiting>();
	}
	

	gameObject->AddComponent<GameEngine::FSM>(m_pWaitingEggState.get(),
		gameObject->GetComponent<GameEngine::AnimationComponent>());

	gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_pWaitingEggState.get(), m_pBreakingEggState.get(),
		m_pIsEggAnimationWaiting.get());
	gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_pBreakingEggState.get(), m_pBrokenEggState.get(),
		m_pIsEggBroken.get());

	m_pScene->Add(std::move(gameObject));
}
