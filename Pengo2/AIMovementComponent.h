#pragma once
#include <BaseComponent.h>
#include <Helpers.h>
#include <AnimationComponent.h>
#include <TransformComponent.h>

class AIMovementComponent final : public GameEngine::BaseComponent
{

public:
	AIMovementComponent(GameEngine::GameObject* pGameObject);
	AIMovementComponent(const AIMovementComponent& other) = delete;
	AIMovementComponent(AIMovementComponent&& other) = delete;
	AIMovementComponent& operator=(const AIMovementComponent& other) = delete;
	AIMovementComponent& operator=(AIMovementComponent&& other) = delete;
	~AIMovementComponent() = default;

	void Update() override;
	void ChangePosition(const glm::vec3& pos);
private:
	GameEngine::AnimationComponent* m_pAnimationComponent;
	GameEngine::TransformComponent* m_pTranformComponent;
};

