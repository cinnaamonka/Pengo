#include "Subject.h"
#include "IObserver.h"

namespace GameEngine
{
    Subject::Subject() : message_(0) {
        std::cout << "Hi, I'm the Subject.\n";
    }

    Subject::~Subject() {
        std::cout << "Goodbye, I was the Subject.\n";
    }

    void Subject::Attach(IObserver* observer) {
        list_observer_.push_back(observer);
    }

    void Subject::Detach(IObserver* observer) {
        list_observer_.remove(observer);
    }

    void Subject::Notify() {
        std::list<IObserver*>::iterator iterator = list_observer_.begin();
        HowManyObserver();
        while (iterator != list_observer_.end()) {
            (*iterator)->Notify(message_);
            ++iterator;
        }
    }

    void Subject::CreateMessage(int message) {
        message_ = message;
        Notify();
    }

    void Subject::HowManyObserver() {
        std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
    }

    void Subject::SomeBusinessLogic() {
        Notify();
        std::cout << "I'm about to do some thing important\n";
    }
}
