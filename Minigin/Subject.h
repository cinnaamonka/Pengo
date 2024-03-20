#pragma once
#include <list>
#include <vector>
#include <memory>
#include <functional>

#include "Observers.h"

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

		void AddObserver(std::unique_ptr <Observer<T>> observer)
		{
			m_pObservers.push_back(std::move(observer));   
		}
		
		void RemoveObserver(Observer<T>* observer)
		{
			const auto& it = std::find(begin(m_pObservers), end(m_pObservers), observer);
			if (it != end(m_pObservers)) m_pObservers.erase(it);
		}
	
		template <typename DataType>
		void Notify(GameObject* gameObject, DataType data)
		{
			for (std::unique_ptr <Observer<T>> observer : m_pObservers)
			{
				
				observer->Notify(gameObject, data);
			}
		}

	private:
		// unqiue pointer because after subject will be deleted, observers will be deallocated by themself
		std::list<std::unique_ptr<Observer<T>>> m_pObservers;
	};
}


