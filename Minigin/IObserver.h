#pragma once

namespace GameEngine
{
    template<typename T>
    class IObserver
    {
    public:
        virtual ~IObserver() {};
        virtual void Notify(const T& messageFromSubject) = 0;
    };
}
