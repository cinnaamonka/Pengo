#pragma once

#include "BaseComponent.h"

#include <deque>

namespace GameEngine
{
	class TextComponent;

	class FPS : public BaseComponent
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

		TextComponent* m_TextComponent;

	};
}

