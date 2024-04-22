#pragma once
#include <memory>
#include <GameObject.h>

class EnemyActor final
{
public:
	EnemyActor();
	~EnemyActor() = default;

	EnemyActor(const EnemyActor& other) = delete;
	EnemyActor& operator=(const EnemyActor& other) = delete;
	EnemyActor(EnemyActor&& other) noexcept = delete;
	EnemyActor& operator=(EnemyActor&& other) noexcept = delete;

	virtual std::unique_ptr<GameEngine::GameObject>& GetActorGameObject();
private:
	std::unique_ptr<GameEngine::GameObject> m_pEnemy;
};

