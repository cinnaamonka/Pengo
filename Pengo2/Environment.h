#pragma once
#include <vector>
#include <memory>
#include <string>
#include <Subject.h>

#include <BaseComponent.h>

#include "BaseBlock.h"
#include "IObserver.h"

#include <Scene.h>

class GameObject;

using namespace GameEngine;

class Environment final: public GameEngine::BaseComponent
{
public:
	Environment(GameEngine::GameObject* pGameObject,const std::string& filename,GameEngine::Scene* scene);
	~Environment() = default; 

	Environment(const Environment& other) = delete; 
	Environment& operator=(const Environment& other) = delete; 
	Environment(Environment&& other) noexcept = delete; 
	Environment& operator=(Environment&& other) noexcept = delete; 

	void CheckCollision(Rect& shape);

	void SetCollisionCanBeChecked(bool canBeChecked)
	{
		m_CanCollisionBeChecked = canBeChecked;
	}

	void Update() override;
	
	void SetActor(GameEngine::GameObject* pActor)
	{
		m_pPlayer = pActor;
	}
	template<typename T>
	void AttachObserver(GameEngine::IObserver<T>* pObserver)
	{
		if constexpr (std::is_same_v<T, GameEngine::CollisionState>)
		{
			m_CollisionStateChanged.Attach(pObserver);
		}
	}
private:
	void ResetHorizontalPosition(Rect& actorShape, HitInfo& hitInfo);
	void ResetVerticalPosition(Rect& actorShape, HitInfo& hitInfo);
private:
	std::vector<std::unique_ptr<BaseBlock>> m_pBlocks;
	std::vector<std::vector<glm::vec3>> m_Vertices;

	bool m_CanCollisionBeChecked;

	GameEngine::GameObject* m_pPlayer;
	GameEngine::Subject<GameEngine::CollisionState> m_CollisionStateChanged; 
};

