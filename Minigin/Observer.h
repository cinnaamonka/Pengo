#pragma once
#include <iostream>

#include "GameObject.h"

namespace GameEngine
{
	class GameObject;

	enum class Event
	{
		PlayerDeath,
		DecreaseLifesAmount,
		ChangeScore,
	};

	struct EventStruct
	{
		Event type;
	};

	template <typename T>
	class Observer
	{
	public:
		virtual ~Observer() = default;

		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;

		virtual void OnNotify(Event event, GameObject* gameObject) = 0;
	protected:
		Observer() = default;
	};

	//class LivesObserver : public Observer
	//{
	//public:
	//	virtual void OnNotify(Event event, GameObject* gameObject) override
	//	{
	//		switch (event)
	//		{
	//		case Event::PlayerDeath:
	//			gameObject = nullptr;
	//			break;
	//	/*	case Event::ChangeScore:
	//			gameObject->GetComponent<GameEngine::ScoreComponent>()->SetScore()
	//			break;*/
	//		}

	//	}
	//};

};



