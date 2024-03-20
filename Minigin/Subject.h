#pragma once

#include <iostream>
#include <list>
#include <memory>
#include "ISubject.h"
#include "IObserver.h"

namespace GameEngine
{
	template<typename T>
	class Subject : public ISubject<T> 
	{
	public:
		Subject() : message_(T()) {}
		virtual ~Subject() {}

		void Attach(IObserver<T>* observer) override 
		{
			list_observer_.push_back(observer);
		}

		void Detach(IObserver<T>* observer) override 
		{
			list_observer_.remove(observer);
		}
		void Notify() 
		{
			typename std::list<IObserver<T>*>::iterator iterator = list_observer_.begin(); 
			HowManyObserver(); 
			while (iterator != list_observer_.end()) 
			{
				(*iterator)->Notify(message_);  
				++iterator;
			}
		}

		void CreateMessage(const T& message) 
		{
			message_ = message;
			Notify();
		}

		void HowManyObserver() 
		{
			std::cout << "There are " << list_observer_.size() << " observers in the list." << std::endl;
		}

		void SomeBusinessLogic()
		{
			// Some business logic here
		}

	private:
		std::list<IObserver<T>*> list_observer_;
		T message_;
	};

}
