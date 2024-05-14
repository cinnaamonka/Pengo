#include "EggObserver.h"
#include <TransformComponent.h>
#include <TextureComponent.h>
#include <RenderComponent.h>
#include <GameObject.h>
#include <BoxColliderComponent.h>
#include <FSM.h>
#include <AnimationComponent.h>


EggObserver::EggObserver(GameEngine::Scene* scenePtr)
{
	m_ScenePtr = scenePtr;
}


void EggObserver::Notify(const glm::vec3& message_from_subject)
{
	if (m_BreakingEggState)
	{
		m_BreakingEggState.release();
	}
	if (m_IsEggBroken)
	{
		m_IsEggBroken.release();
	}
	if (m_pBrokenEggState)
	{
		m_pBrokenEggState.release();
	}
	if (m_WaitingEggState)
	{
		m_WaitingEggState.release();
	}
	if (m_IsEggAnimationWaiting)
	{
		m_IsEggAnimationWaiting.release();
	}

	auto gameObject = std::make_unique<GameEngine::GameObject>();

	gameObject->AddComponent<GameEngine::TransformComponent>(message_from_subject);
	gameObject->AddComponent<GameEngine::TextureComponent>("Egg.tga", m_HorizontalAmountOfFrames);
	gameObject->AddComponent<GameEngine::AnimationComponent>();
	gameObject->AddComponent<GameEngine::RenderComponent>();
	
	auto textureSizeX = gameObject->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().x / m_HorizontalAmountOfFrames;
	auto textureSizeY = gameObject->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().y;

	gameObject->GetComponent<GameEngine::TransformComponent>()->SetDimensions({ 0, 0,textureSizeX,textureSizeY });

	m_BreakingEggState	    = std::make_unique<BreakingEggState>();
	m_IsEggBroken		    = std::make_unique<IsEggBroken>();
	m_pBrokenEggState	    = std::make_unique<BrokenEggState>();
	m_WaitingEggState	    = std::make_unique<WaitingState>();
	m_IsEggAnimationWaiting = std::make_unique<IsWaiting>();

	gameObject->AddComponent<GameEngine::FSM>(m_WaitingEggState.get(),
		gameObject->GetComponent<GameEngine::AnimationComponent>());

	gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_WaitingEggState.get(), m_BreakingEggState.get(),
		m_IsEggAnimationWaiting.get());
	gameObject->GetComponent<GameEngine::FSM>()->AddTransition(m_BreakingEggState.get(), m_pBrokenEggState.get(),
		m_IsEggBroken.get());

	m_ScenePtr->Add(std::move(gameObject));
}
