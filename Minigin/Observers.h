#pragma once
#include <iostream>

#include "TextComponent.h"
#include "GameObject.h"
#include "Subject.h"
#include "IObserver.h"


namespace GameEngine
{
	class Observer : public IObserver {
	public:
		Observer(Subject& subject);

		virtual ~Observer() {
			std::cout << "Goodbye, I was the Observer \"" << number_ << "\".\n";
		}

		void Update(const int message_from_subject) override;

		void RemoveMeFromTheList();

		void PrintInfo() const;

	private:
		Subject& subject_;
		int message_from_subject_;

		static int static_number_;
		int number_;
	};
};



