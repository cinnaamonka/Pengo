#include "Observers.h"


namespace GameEngine
{
	int GameEngine::Observer::static_number_ = 0;

	Observer::Observer(Subject& subject) : subject_(subject), message_from_subject_(0)
	{
		Observer::static_number_++;
		number_ = Observer::static_number_;
		subject_.Attach(this);
		std::cout << "Hi, I'm the Observer \"" << number_ << "\".\n";
	}

	void Observer::Notify(const int message_from_subject) {
		message_from_subject_ = message_from_subject;
		PrintInfo();
	}

	void Observer::RemoveMeFromTheList() {
		subject_.Detach(this);
		std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
	}

	void Observer::PrintInfo() const {
		std::cout << "Observer \"" << number_ << "\": a new message is available --> " << message_from_subject_ << "\n";
	}
}
