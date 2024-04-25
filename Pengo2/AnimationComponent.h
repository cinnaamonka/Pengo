#pragma once
#include <BaseComponent.h>
#include <StatesAndTransitions.h>
#include <Helpers.h>


class AnimationComponent final: public GameEngine::BaseComponent
{

public:
	AnimationComponent(GameEngine::GameObject* pGameObject);
	AnimationComponent(const AnimationComponent& other) = delete;
	AnimationComponent(AnimationComponent&& other) = delete;
	AnimationComponent& operator=(const AnimationComponent& other) = delete;
	AnimationComponent& operator=(AnimationComponent&& other) = delete;
	~AnimationComponent() = default;


	void Update() override;
	void ChangeTexture(int currentAnimationFrame, int currentHorizontalOffset = 0, int currentVerticalOffset = 0);


};

