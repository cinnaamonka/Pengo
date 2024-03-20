#pragma once

#include "IObserver.h"

namespace GameEngine 
{
    template<typename T>
    class ISubject 
    {
    public:
        virtual ~ISubject() {};
        virtual void Attach(IObserver<T>* observerPtr) = 0;
        virtual void Detach(IObserver<T>* observerPtr) = 0;
        virtual void Notify() = 0;
    };
}

