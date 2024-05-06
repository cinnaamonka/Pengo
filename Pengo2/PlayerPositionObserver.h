#pragma once
#include <BaseComponent.h>
#include <IObserver.h>
#include <Helpers.h>

#include <glm/vec3.hpp>
#include <glm/glm.hpp>

class GameEngine::GameObject; 

class PlayerPositionObserver : public GameEngine::BaseComponent ,public GameEngine::IObserver<glm::vec3> 
{
public:

	PlayerPositionObserver(GameEngine::GameObject* pGameObject);
	~PlayerPositionObserver() = default;
	PlayerPositionObserver(const PlayerPositionObserver& other) = delete;
	PlayerPositionObserver& operator=(const PlayerPositionObserver& other) = delete;
	PlayerPositionObserver(PlayerPositionObserver&& other) = delete;

	void Notify(const glm::vec3& message_from_subject) override;

private:
	bool AreVectorsCollinear(const glm::vec3& v1, const glm::vec3& v2,float tolerance = 0.0f) const;
	bool AreOnSameLine(const glm::vec3& referencePoint, const glm::vec3& pos1, const glm::vec3& pos2) const;
private:
	const int m_Radius = 20;
};

