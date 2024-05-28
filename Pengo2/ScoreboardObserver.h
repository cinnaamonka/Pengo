#pragma once
#include "memory"
#include <GameObject.h>
#include <BaseComponent.h>

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <IObserver.h>
#include <Scene.h>
#include "Structs.h"

class ScoreboardObserver : public GameEngine::IObserver<ScoreBoardData>, public GameEngine::BaseComponent
{
public:
	ScoreboardObserver(GameEngine::GameObject* gameObject,GameEngine::Scene* scenePtr);
	~ScoreboardObserver() = default;
	ScoreboardObserver(const ScoreboardObserver& other) = delete;
	ScoreboardObserver(ScoreboardObserver&& other) = delete;
	ScoreboardObserver& operator=(const ScoreboardObserver& other) = delete;
	ScoreboardObserver& operator=(ScoreboardObserver&& other) = delete;

	void Notify(const ScoreBoardData& message_from_subject) override;
private:
	GameEngine::Scene* m_ScenePtr;
};
