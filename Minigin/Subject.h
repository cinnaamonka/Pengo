#pragma once

#include <iostream>
#include <list>
#include <memory>
#include "ISubject.h"
#include "IObserver.h"

namespace GameEngine
{
	class Subject : public ISubject {
	public:
		Subject();
		virtual ~Subject();

		void Attach(IObserver* observer) override;
		void Detach(IObserver* observer) override;
		void Notify() override;

		void CreateMessage(int message);
		void HowManyObserver();
		void SomeBusinessLogic();

	private:
		std::list<IObserver*> list_observer_;
		int message_;
	};
}
