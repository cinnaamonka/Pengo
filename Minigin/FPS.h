#pragma once
#include "Components.h"
#include <deque>

namespace GameEngine
{
	class FPS : public Component
	{
	public:
		FPS(GameObject* GOptr);

		void Update() override;

		double GetAverageFPS() const
		{
			return m_AverageFPS;
		}

	private:
		std::deque<double> m_FPSCollection;
		const int m_AverageFramesAmount;
		double m_AverageFPS;
	};
}

