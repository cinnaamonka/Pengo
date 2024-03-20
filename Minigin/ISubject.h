#pragma once

#include "IObserver.h"

namespace GameEngine
{
    class GameObject;

    class ISubject {
    public:
        virtual ~ISubject() {};
        virtual void Attach(IObserver* observer) = 0;
        virtual void Detach(IObserver* observer) = 0;
        virtual void Notify() = 0;
    };
}


