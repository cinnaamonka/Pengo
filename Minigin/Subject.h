#pragma once
#include <list>
#include <vector>
#include <memory>
#include <functional>

#include "Observer.h"

namespace GameEngine
{
	class GameObject;

	enum class Event;

	template <class T>
	class Subject final
	{
	public:
		Subject() = default;
		~Subject() = default;
		
		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete; 
		Subject& operator=(Subject&& other) = delete;

		void AddObserver(Observer<T>* observer)
		{
			m_Observers.push_back(observer); 
		}
		void AddObserver(const std::function<void(const T&)>& callback)
		{
			m_Observers.push_back(observer);
		}
		void RemoveObserver(Observer<T>* observer)
		{
			const auto& it = std::find(begin(m_Observers), end(m_Observers), observer); 
			if (it != end(m_Observers)) m_Observers.erase(it); 
		}
		void RemoveObserver(const std::function<void(const T&)>& callback)
		{
			const auto& it = std::find(begin(m_Observers), end(m_Observers), observer);
			if (it != end(m_Observers)) m_Observers.erase(it);
		}
		
		void OnNotify(const T& data)
		{
			for (const auto& observer : m_Observers)
			{
				observer->Notify(data);
			}
			for (const auto& function : m_Functions)
			{
				function(data);
			}
		}

	private:
		// unqiue pointer because after subject will be deleted, observers will be deallocated by themself
		std::list<std::unique_ptr<Observer<T>>> m_pObservers;
		std::vector<std::function<void(const T&)>> m_Functions;
	};
}


