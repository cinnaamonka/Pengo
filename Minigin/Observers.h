#pragma once
#include <iostream>

#include "TextComponent.h"
#include "GameObject.h"

namespace GameEngine
{
    template <typename Data>
    class Observer
    {
    public:
        virtual ~Observer() = default;
        virtual void Notify(GameObject* gameObject, Data data) = 0;
    };

    class ScoreObserver final : public Observer<int>
    {
    public:
        void Notify(GameEngine::GameObject* gameObject, int score) override
        {
            if (gameObject->HasComponent<TextComponent>())
            {
                gameObject->GetComponent<TextComponent>()->SetText("Score: " + std::to_string(score));
            }
        }
    };

};



