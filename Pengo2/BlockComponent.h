#pragma once
#include <BaseComponent.h>

class GameEngine::GameObject;
class PushObserver;

class BlockComponent:public GameEngine::BaseComponent
{
public:
	BlockComponent(GameEngine::GameObject* pGameObject); 
	~BlockComponent() = default;

	BlockComponent(const BlockComponent& other) = delete;
	BlockComponent& operator=(const BlockComponent& other) = delete;
	BlockComponent(BlockComponent&& other) noexcept = delete;
	BlockComponent& operator=(BlockComponent&& other) noexcept = delete;

	void PushBlock();
private:
	GameEngine::GameObject* m_pGameObjectReference;
	PushObserver* m_pPushObserver;
};

