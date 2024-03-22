#pragma once

#include <iostream>
#include <list>
#include <string>
#include <memory>
#include "IObserver.h"

namespace GameEngine
{
	template<typename T>
	class Subject
	{
	public:
		Subject() : m_Message(T()) {}
		virtual ~Subject()
		{

		}

		void Attach(IObserver<T>* observerPtr) 
		{
			m_ObserversPtr.push_back(observerPtr);
		}

		void Detach(IObserver<T>* observerPtr) 
		{
			m_ObserversPtr.remove(observerPtr);
		}
		void Notify()
		{
			typename std::list<IObserver<T>*>::iterator iterator = m_ObserversPtr.begin();
			HowManyObserver();
			while (iterator != m_ObserversPtr.end())
			{
				(*iterator)->Notify(m_Message);
				++iterator;
			}
		}

		void CreateMessage(const T& message)
		{
			m_Message = message;
			Notify();
		}
		void HowManyObserver()
		{
			std::cout << "There are " << m_ObserversPtr.size() << " observers in the list." << std::endl;
		}


	private:
		std::list<IObserver<T>*> m_ObserversPtr;
		T m_Message;

	};
};

