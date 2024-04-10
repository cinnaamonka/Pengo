#pragma once
#include <vector>
#include <memory>
#include <string>

#include <BaseComponent.h>

#include "BaseBlock.h"

#include <Scene.h>

class GameObject;

class Environment final: public GameEngine::BaseComponent 
{
public:
	Environment(GameEngine::GameObject* pGameObject,const std::string& filename,GameEngine::Scene* scene);
	~Environment() = default; 

	Environment(const Environment& other) = delete; 
	Environment& operator=(const Environment& other) = delete; 
	Environment(Environment&& other) noexcept = delete; 
	Environment& operator=(Environment&& other) noexcept = delete; 

	void CheckCollision(Rect& shape, glm::vec2& velocity);

	void SetCollisionCanBeChecked(bool canBeChecked)
	{
		m_CanCollisionBeChecked = canBeChecked;
	}

	void Update() override;
	
	void SetActor(GameEngine::GameObject* pActor)
	{
		m_pPlayer = pActor;
	}
private:
	void ResetHorizontalPosition(glm::vec2& actorVelocity, Rect& actorShape, HitInfo& hitInfo) const;
private:
	std::vector<std::unique_ptr<BaseBlock>> m_pBlocks;
	std::vector<std::vector<glm::vec3>> m_Vertices;

	bool m_CanCollisionBeChecked;

	GameEngine::GameObject* m_pPlayer;
};

