#pragma once
#include <iostream>

#include "TextComponent.h"
#include "GameObject.h"
#include "Subject.h"
#include "IObserver.h"


namespace GameEngine 
{
    namespace GameEngine
    {
        template<typename T>
        class Observer : public IObserver<T> 
        {
        public:
            Observer(Subject<T>& subject) : subject_(subject) 
            {
                subject_.Attach(this);
                std::cout << "Hi, I'm the Observer.\n";
            }

            virtual ~Observer() 
            {
                std::cout << "Goodbye, I was the Observer \"" << number_ << "\".\n";
                subject_.Detach(this);
            }

            void Notify(const T& message_from_subject) override
            {
                message_from_subject_ = message_from_subject;
                PrintInfo();
            }

            void RemoveMeFromTheList() 
            {
                subject_.Detach(this);
                std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
            }

            void PrintInfo() const 
            {
                std::cout << "Observer \"" << number_ << "\": a new message is available --> " << message_from_subject_ << "\n";
            }

        private:
            Subject<T>& subject_;
            T message_from_subject_;

            int number_;
        };
    }
}




