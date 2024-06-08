#pragma once

#include "BaseComponent.h"

#include <deque>

namespace GameEngine
{
	class TextComponent;

	class FPS final: public BaseComponent
	{
	public:
		FPS(GameObject* GOptr);
	
		~FPS() = default;
		FPS(const FPS& other) = delete;
		FPS(FPS&& other) noexcept = delete;
		FPS& operator=(const FPS& other) = delete;
		FPS& operator=(FPS&& other) noexcept = delete;

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

