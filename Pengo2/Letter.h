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
	void DeleteInput();

	void SetLetterIndex(int index) 
	{
		m_LetterIndex = index; 
	}
	int GetLetterIndex() const
	{
		return m_LetterIndex; 
	}
	char GetCurrentLetter() const 
	{ 
		return m_CurrentLetter;
	}
	void SetCurrentLetter(char letter) 
	{ 
		m_CurrentLetter = letter; 
	}
	
private:
	static std::unique_ptr<StaticLetterState> m_pStaticLetterState;
	static std::unique_ptr<FlyckeringLetterState> m_pFlyckeringLetterState;
	static std::unique_ptr<ShouldStartFlyckering> m_pShouldStartFlyckering;
	static std::unique_ptr<ShouldStopFlyckering> m_pShouldStopFlyckering;

	int m_LetterIndex = 0;
	char m_CurrentLetter = 'A';
};

