#pragma once
#include <BaseComponent.h>
#include <StatesAndTransitions.h>


class GameEngine::Blackboard;

class AnimationComponent final: public GameEngine::BaseComponent
{

public:
	AnimationComponent(GameEngine::GameObject* pGameObject, int framesPerSec);
	AnimationComponent(const AnimationComponent& other) = delete;
	AnimationComponent(AnimationComponent&& other) = delete;
	AnimationComponent& operator=(const AnimationComponent& other) = delete;
	AnimationComponent& operator=(AnimationComponent&& other) = delete;
	~AnimationComponent() = default;

	std::unique_ptr<GameEngine::Blackboard>& GetBlackboard() { return m_pBlackboard; }

	template <typename T>
	void ChangeData(const std::string& key, T value)
	{
		m_pBlackboard->ChangeData(key, value);
	}

	template <typename T>
	void AddData(const std::string& key, T value)
	{
		m_pBlackboard->AddData(key, value);
	}

	template <typename T>
	T GetData(const std::string& key)
	{
		return m_pBlackboard->GetData<T>(key);
	}

	void Update() override;
	void ChangeTexture(int currentAnimationFrame, int currentHorizontalOffset = 0, int currentVerticalOffset = 0);
private:

	std::unique_ptr<GameEngine::Blackboard> m_pBlackboard;

};

