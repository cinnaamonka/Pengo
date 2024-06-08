#pragma once
#include <BaseComponent.h>
#include <IObserver.h>
#include <Helpers.h>
#include <AnimationComponent.h>

class GameObject;

struct BlockCollisionInfo
{
	int index;
	GameEngine::HitInfo hitInfo;
	bool isPushed;
};

class BlockObserver: public GameEngine::BaseComponent, public GameEngine::IObserver<BlockCollisionInfo>
{
public:
	BlockObserver(GameEngine::GameObject* pGameObject);
	~BlockObserver() = default;
	BlockObserver(const BlockObserver& other) = delete;
	BlockObserver& operator=(const BlockObserver& other) = delete;
	BlockObserver(BlockObserver&& other) = delete;

	void Notify(const BlockCollisionInfo& message_from_subject) override;
private:
	const float m_TopOffset = 0.9f;
	const float m_BottomOffset = 0.1f;
	const int m_PushSpeed = 10;
};

