#pragma once
#include <BaseComponent.h>
#include <IObserver.h>
#include <Helpers.h>

#include <glm/vec3.hpp>
#include <glm/glm.hpp>

class EnemyDirectionObserver : public GameEngine::IObserver<GameEngine::EnemyInfo>, public GameEngine::BaseComponent
{
public:
	EnemyDirectionObserver(GameEngine::GameObject* pGameObject, int index);
	~EnemyDirectionObserver() = default;
	EnemyDirectionObserver(const EnemyDirectionObserver& other) = delete;
	EnemyDirectionObserver(EnemyDirectionObserver&& other) = delete;
	EnemyDirectionObserver& operator=(const EnemyDirectionObserver& other) = delete;
	EnemyDirectionObserver& operator=(EnemyDirectionObserver&& other) = delete;

	int GetIndex() const
	{
		return m_Index;
	}
	void SetIndex(int index)
	{
		m_Index = index;
	}

	void Notify(const GameEngine::EnemyInfo& direction) override;

private:
	int m_Index;

};

