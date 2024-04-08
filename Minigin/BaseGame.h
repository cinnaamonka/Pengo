#pragma once
class BaseGame
{
public:
	BaseGame() = default;
	BaseGame(const BaseGame& other) = delete;
	BaseGame& operator=(const BaseGame& other) = delete;
	BaseGame(BaseGame&& other) = delete;
	BaseGame& operator=(BaseGame&& other) = delete;
	virtual ~BaseGame() {};


	virtual void InitializeInputSystem() = 0;
};

