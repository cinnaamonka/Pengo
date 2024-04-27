#pragma once
#include <vector>
#include <memory>
#include <string>
#include <Helpers.h>
#include <Subject.h>

#include <BaseComponent.h>

#include "BaseBlock.h"
#include "IObserver.h"
#include "BlockObserver.h"

#include <Scene.h>

#include <glm/vec3.hpp>
#include <glm/glm.hpp>

class GameObject;

class Environment final : public GameEngine::BaseComponent
{
public:
	Environment(GameEngine::GameObject* pGameObject, const std::string& filename, GameEngine::Scene* scene);
	~Environment() {};

	Environment(const Environment& other) = delete;
	Environment& operator=(const Environment& other) = delete;
	Environment(Environment&& other) noexcept = delete;
	Environment& operator=(Environment&& other) noexcept = delete;

	void CheckCollision();
	void CheckBlocksCollision(GameEngine::GameObject* pGameObject);

	void Update() override;

	void SetActor(GameEngine::GameObject* pActor)
	{
		m_pPlayer = pActor;
	}
	template<typename T>
	void AttachObserver(GameEngine::IObserver<T>* pObserver)
	{
		if (std::is_same_v<T, GameEngine::HitInfo>)
		{
			m_CollisionHitInfoChanged.Attach(pObserver);
		}
	}

	void PushBlock();

	void CreateBlocksCollection(std::vector<GameEngine::Block> blocks, const std::string& name, const std::string& tag,
		int& offset, GameEngine::Scene* scene, bool IsBreakable, int clipTextureAmount = 1);
	
private:
	std::vector<GameEngine::GameObject*> m_pBlocks;
	
	std::vector<GameEngine::Block> m_LevelVertices;

	GameEngine::GameObject* m_pPlayer;
	GameEngine::GameObject* m_pBorderBlock;

	GameEngine::Subject<GameEngine::HitInfo> m_CollisionHitInfoChanged;
	GameEngine::Subject<BlockCollisionInfo> m_BlockCollisionInfo;

	int m_PushBlockIndex = -1;

	const int m_BorderWidth;
	const int m_BorderLength;
	const int m_BorderHeight;
};

