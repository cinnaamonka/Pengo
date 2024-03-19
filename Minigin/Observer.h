#pragma once
#include <iostream>

#include "GameObject.h"

namespace GameEngine
{
	template <typename T>
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const T& data) = 0;
		virtual void OnSubjectDestroy() {};
	};

	template <typename T>
	class ScoreObserver : public Observer<T>
	{
	public:
		ScoreObserver() {}

		void Notify(const T& data) override;
	};
};



