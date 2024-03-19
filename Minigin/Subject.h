#pragma once
#include <list>
#include <memory>

namespace GameEngine
{
	class Observer;
	class GameObject;

	enum class Event;

	class Subject final
	{
	public:
		Subject() = default;
		~Subject() = default;
		
		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete; 
		Subject& operator=(Subject&& other) = delete;

		void AddObserver(std::unique_ptr<Observer> pObserver);
		void RemoveObserver(std::unique_ptr<Observer> pObserver);
		// should be done protected probably
		void OnNotify(GameObject* obj, Event event) const;

	private:
		// unqiue pointer because after subject will be deleted, observers will be deallocated by themself
		std::list<std::unique_ptr<Observer>> m_pObservers;
	};
}


