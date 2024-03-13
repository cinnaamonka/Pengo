#pragma once
class BaseCommand
{
public:
	explicit BaseCommand() = default;
	virtual ~BaseCommand() = default;

	BaseCommand(const BaseCommand& other) = delete;
	BaseCommand& operator=(const BaseCommand& other) = delete;
	BaseCommand(BaseCommand&& other) noexcept = delete;
	BaseCommand& operator=(BaseCommand&& other) noexcept = delete;

	virtual void Execute() = 0;
};

