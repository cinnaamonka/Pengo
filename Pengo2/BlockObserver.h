#pragma once
#include <BaseComponent.h>
#include <IObserver.h>
#include <Helpers.h>

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
};

