#pragma once
#include <windows.h>
#include <SDL.h>

#include <memory>


#include "BaseCommand.h"

namespace GameEngine
{
	enum class InputState : unsigned char
	{
		Pressed,
		Released,
		Previous
	};

	class BaseInputDevice
	{
	public:
		virtual ~BaseInputDevice() = default;

		virtual void Update() = 0;

		virtual bool IsPressed(int button) = 0;
		virtual bool IsReleased(int button) = 0;
		virtual bool IsPrevious(int button) = 0;
		virtual int GetIndex() const = 0;

		virtual void HandleInput() = 0;

		template<typename BindingType>
		void AddCommand(BindingType binding, std::unique_ptr<BaseCommand> command, std::vector<std::pair<BindingType,
			std::unique_ptr<BaseCommand>>>& commandVector)
		{
			commandVector.push_back(std::make_pair(binding, std::move(command)));
		}

		template<typename BindingType>
		void RemoveCommand(BindingType) {};
	};

}