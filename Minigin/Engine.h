#pragma once

#include <functional>
#include <string>
#include <memory>
#include "BaseGame.h"
//#include "vld.h" 

namespace GameEngine
{
	class Engine
	{
	public:
		explicit Engine(const std::string& dataPath);
		~Engine();
		void Run(const std::function<std::unique_ptr<BaseGame>()>& load);

		Engine(const Engine& other) = delete;
		Engine(Engine&& other) = delete;
		Engine& operator=(const Engine& other) = delete;
		Engine& operator=(Engine&& other) = delete;

	private:
		double m_Lag = 0;
	};
}