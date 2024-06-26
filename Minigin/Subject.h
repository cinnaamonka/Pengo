#pragma once

#include <list>
#include <memory>
#include "IObserver.h"

namespace GameEngine
{
	template<typename T>
	class Subject final
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

	private:
		std::list<IObserver<T>*> m_ObserversPtr;
		T m_Message;

	};
};

