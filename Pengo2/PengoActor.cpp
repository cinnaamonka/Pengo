#include "PengoActor.h"

#include <TransformComponent.h>
#include <TextureComponent.h>
#include <RenderComponent.h>
#include <BoxColliderComponent.h>
#include <ResourceManager.h>
#include <ActorComponent.h>
#include "HitObserver.h"

#include <Helpers.h>
#include <Texture2D.h>
#include <FSM.h>
#include <AnimationComponent.h>

PengoActor::PengoActor()
{

	m_pActor = std::make_unique<GameEngine::GameObject>();
	m_pActor->AddComponent<GameEngine::BoxCollider>(250, 320, 20, 20);
	m_pActor->AddComponent<GameEngine::TransformComponent>(glm::vec3(250, 320, 0));
	m_pActor->AddComponent<GameEngine::TextureComponent>("PengoCharacter.tga");
	m_pActor->AddComponent<GameEngine::ActorComponent>();
	m_pActor->AddComponent<GameEngine::AnimationComponent>();
	m_pActor->AddComponent<GameEngine::HealthObserver>(); 

	auto textureSizeX = m_pActor->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().x / m_HorizontalAmountOfFrames;
	auto textureSizeY = m_pActor->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().y / m_VerticalAmountOfFrames;

	m_pActor->GetComponent<GameEngine::TransformComponent>()->SetDimensions({ 0, 0,textureSizeX,textureSizeY });

    auto actorComponent = m_pActor->GetComponent<GameEngine::ActorComponent>();
    auto healthObserver = m_pActor->GetComponent<GameEngine::HealthObserver>();
    actorComponent->AttachObserver<GameEngine::State>(healthObserver); 

	m_IdleState = std::make_unique<IdleState>();
	m_RunningState = std::make_unique<RunningState>();
	m_PushingState = std::make_unique<PushingState>();
	m_DyingState = std::make_unique<PlayerDyingState>();

	m_IsInputGiven = std::make_unique <IsInputGiven>();
	m_IsNotInputGiven = std::make_unique<IsInputNotGiven>();
	m_IsBlockPushed = std::make_unique<IsBlockPushed>(); 
	m_IsBlockNotPushed = std::make_unique<IsBlockNotPushed>();
	m_IsKilled = std::make_unique<IsKilled>(); 

	m_pActor->AddComponent<GameEngine::FSM>(m_IdleState.get(), m_pActor->GetComponent<GameEngine::AnimationComponent>());
	m_pActor->GetComponent<GameEngine::FSM>()->AddTransition(m_IdleState.get(), m_RunningState.get(), m_IsInputGiven.get());
	m_pActor->GetComponent<GameEngine::FSM>()->AddTransition(m_RunningState.get(), m_IdleState.get(), m_IsNotInputGiven.get());
	m_pActor->GetComponent<GameEngine::FSM>()->AddTransition(m_IdleState.get(), m_PushingState.get(), m_IsBlockPushed.get());
	m_pActor->GetComponent<GameEngine::FSM>()->AddTransition(m_PushingState.get(), m_IdleState.get(), m_IsBlockNotPushed.get());
	m_pActor->GetComponent<GameEngine::FSM>()->AddTransition(m_IdleState.get(), m_DyingState.get(), m_IsKilled.get());

	m_pActor->AddComponent<HitObserver>();
	m_pActor->AddComponent<GameEngine::RenderComponent>();

	m_ReferenceToCharacterPengo = m_pActor.get();
}

PengoActor::~PengoActor()
{
}

HitObserver* PengoActor::GetHitObserver() const
{
	return m_pActor->GetComponent<HitObserver>();
}


std::unique_ptr<GameEngine::GameObject>& PengoActor::GetActorGameObject()
{
	return m_pActor;
}


