#pragma once
#include <iostream>
namespace GameEngine
{
	class GameObject;

	enum class Event
	{
		PlayerDeath,
		DecreaseLifesAmount
	};

	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;

		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;

		virtual void OnNotify(Event event, GameObject* gameObject) = 0;
	};

	class LivesObserver : public Observer
	{
	public:
		virtual void OnNotify(Event event, GameObject* gameObject) override
		{
			if (event == Event::PlayerDeath)
			{
				gameObject = gameObject;
			}
		}
	};

};



