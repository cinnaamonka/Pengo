#pragma once

#include "IObserver.h"

namespace GameEngine 
{
    template<typename T>
    class ISubject 
    {
    public:
        virtual ~ISubject() {};
        virtual void Attach(IObserver<T>* observer) = 0;
        virtual void Detach(IObserver<T>* observer) = 0;
        virtual void Notify() = 0;
    };
}

