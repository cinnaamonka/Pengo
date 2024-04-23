#pragma once
#include <vector>
#include <memory>
#include <string>
#include <Subject.h>

#include <BaseComponent.h>

#include "BaseBlock.h"
#include "IObserver.h"

#include <Scene.h>

#include <glm/vec3.hpp>
#include <glm/glm.hpp>

class GameObject;

using namespace GameEngine;

class Environment final : public GameEngine::BaseComponent
{
public:
	Environment(GameEngine::GameObject* pGameObject, const std::string& filename, GameEngine::Scene* scene);
	~Environment() = default;

	Environment(const Environment& other) = delete;
	Environment& operator=(const Environment& other) = delete;
	Environment(Environment&& other) noexcept = delete;
	Environment& operator=(Environment&& other) noexcept = delete;

	void CheckCollision(Rect& shape);
	void CheckBlocksCollision(Rect& shape);

	void Update() override;

	void SetActor(GameEngine::GameObject* pActor)
	{
		m_pPlayer = pActor;
	}
	template<typename T>
	void AttachObserver(GameEngine::IObserver<T>* pObserver)
	{
		if constexpr (std::is_same_v<T, GameEngine::HitInfo>)
		{
			m_CollisionHitInfoChanged.Attach(pObserver);
		}
	}

	void PushBlock();

private:
	std::vector<GameEngine::GameObject*> m_pBlocks;
	std::vector<std::vector<glm::vec3>> m_VerticesIceBlocks;
	std::vector<std::vector<glm::vec3>> m_VerticesDiamondBlocks;
	std::vector<std::vector<glm::vec3>> m_BorderVertices;

	GameEngine::GameObject* m_pPlayer;
	GameEngine::GameObject* m_pBorderBlock;

	GameEngine::Subject<HitInfo> m_CollisionHitInfoChanged;

	int m_PushedBlockIndex;
	int m_BorderWidth;
	int m_BorderLength;
	int m_BorderHeight;
	glm::vec3 m_PushDirection;
	bool m_BlockCanBePushed;
};

