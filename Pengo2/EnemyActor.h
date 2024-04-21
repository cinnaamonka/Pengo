#pragma once
#include <memory>
#include <GameObject.h>
#include "Entity.h"

class EnemyActor final : public Entity
{
public:
	EnemyActor();
	~EnemyActor() = default;

	EnemyActor(const EnemyActor& other) = delete;
	EnemyActor& operator=(const EnemyActor& other) = delete;
	EnemyActor(EnemyActor&& other) noexcept = delete;
	EnemyActor& operator=(EnemyActor&& other) noexcept = delete;

private:
	std::unique_ptr<GameEngine::GameObject> m_pEnemy;
};

