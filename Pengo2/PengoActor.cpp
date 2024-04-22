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

PengoActor::PengoActor()
{

	m_pActor = std::make_unique<GameEngine::GameObject>();
	m_pActor->AddComponent<GameEngine::BoxCollider>(250, 350, 20, 20);
	m_pActor->AddComponent<GameEngine::TransformComponent>(glm::vec3(250, 350, 0));
	m_pActor->AddComponent<GameEngine::TextureComponent>("PengoCharacter.tga");
	m_pActor->AddComponent<GameEngine::ActorComponent>();

	m_pBlackboard = std::make_unique<GameEngine::Blackboard>();
	m_pBlackboard->AddData("WasInputGiven", false);
	m_pBlackboard->AddData("NumberOfFrames", int());
	m_pBlackboard->AddData("AnimationTime", float());
	m_pBlackboard->AddData("FramesPerSec", 10);
	m_pBlackboard->AddData("AnimationFrame", int());
	m_pBlackboard->AddData("HorizontalOffset", int());
	m_pBlackboard->AddData("VerticalOffset", int());
	m_pBlackboard->AddData("MovementDirection", glm::vec3());
	m_pBlackboard->AddData("WasBlockPushed", bool());

	auto textureSizeX = m_pActor->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().x / m_HorizontalAmountOfFrames;
	auto textureSizeY = m_pActor->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().y / m_VerticalAmountOfFrames;

	m_pActor->GetComponent<GameEngine::TransformComponent>()->SetDimensions({ 0, 0,textureSizeX,textureSizeY });

	m_IdleState = std::make_unique<GameEngine::IdleState>();
	m_RunningState = std::make_unique<GameEngine::RunningState>();
	m_PushingState = std::make_unique<GameEngine::PushingState>();

	m_IsInputGiven = std::make_unique <GameEngine::IsInputGiven>();
	m_IsNotInputGiven = std::make_unique<GameEngine::IsInputNotGiven>();
	m_IsBlockPushed = std::make_unique<GameEngine::IsBlockPushed>(); 
	m_IsBlockNotPushed = std::make_unique<GameEngine::IsBlockNotPushed>();

	m_pActor->AddComponent<GameEngine::FSM>(m_IdleState.get(), m_pBlackboard.get());
	m_pActor->GetComponent<GameEngine::FSM>()->AddTransition(m_IdleState.get(), m_RunningState.get(), m_IsInputGiven.get());
	m_pActor->GetComponent<GameEngine::FSM>()->AddTransition(m_RunningState.get(), m_IdleState.get(), m_IsNotInputGiven.get());
	m_pActor->GetComponent<GameEngine::FSM>()->AddTransition(m_IdleState.get(), m_PushingState.get(), m_IsBlockPushed.get());
	m_pActor->GetComponent<GameEngine::FSM>()->AddTransition(m_PushingState.get(), m_IdleState.get(), m_IsBlockNotPushed.get());

	m_ReferenceToCharacterPengo = m_pActor.get();

	m_pActor->AddComponent<HitObserver>();
	m_pActor->AddComponent<GameEngine::RenderComponent>();
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


