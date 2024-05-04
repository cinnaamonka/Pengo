#pragma once
#include <BaseComponent.h>
#include <IObserver.h>

#include <glm/vec3.hpp>
#include <glm/glm.hpp>

class EnemyDirectionObserver : public GameEngine::IObserver<glm::vec3>, public GameEngine::BaseComponent
{
	//rule of 5
public:
	EnemyDirectionObserver(GameEngine::GameObject* pGameObject);
	~EnemyDirectionObserver() = default;
	EnemyDirectionObserver(const EnemyDirectionObserver& other) = delete;
	EnemyDirectionObserver(EnemyDirectionObserver&& other) = delete;
	EnemyDirectionObserver& operator=(const EnemyDirectionObserver& other) = delete;
	EnemyDirectionObserver& operator=(EnemyDirectionObserver&& other) = delete;

	void Notify(const glm::vec3& direction) override;

};

