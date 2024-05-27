#pragma once
#include <BaseComponent.h>
#include <memory>
#include "LetterStatesAndTransitions.h"
#include <Scene.h>

class GameEngine::GameObject;
class GameEngine::Scene;

class Letter: public GameEngine::BaseComponent
{
public:
	Letter(GameEngine::GameObject* gameObject);
	~Letter() = default;

	Letter(const Letter& other) = default;
	Letter& operator=(const Letter& other) = default;
	Letter(Letter&& other) noexcept = default;
	Letter& operator=(Letter&& other) noexcept = default;

	static std::unique_ptr<GameEngine::GameObject> AddLetter(const glm::vec3& position);

	void AddAnimation();
	void AddNewInput();
private:
	static std::unique_ptr<StaticLetterState> m_pStaticLetterState;
	static std::unique_ptr<FlyckeringLetterState> m_pFlyckeringLetterState;
	static std::unique_ptr<ShouldStartFlyckering> m_pShouldStartFlyckering;
	static std::unique_ptr<ShouldStopFlyckering> m_pShouldStopFlyckering;
};

