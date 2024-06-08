#pragma once
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>

#include <vector>
#include <memory>
#include <iostream>

#include "Singleton.h"
#include "Controller.h"
#include "Keyboard.h"
#include "BaseCommand.h"
#include "BaseInputDevice.h"

namespace GameEngine
{
	enum class InputDeviceType
	{
		Controller,
		Keyboard
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		virtual ~InputManager() = default;

		InputManager(const InputManager& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager(InputManager&& other) noexcept = delete;
		InputManager& operator=(InputManager&& other) noexcept = delete;

		template<typename T>
		void HandleInput()
		{
			for (const auto& device : m_pDevices)
			{
				if (dynamic_cast<T*>(device.get()) != nullptr)
				{
					static_cast<T*>(device.get())->HandleInput();
				}
			}
		}

		template<typename T>
		void AddDevice(std::unique_ptr<T> device)
		{
			m_pDevices.push_back(std::move(device));
		}

		template<typename T>
		void RemoveDevice()
		{
			m_pDevices.erase(std::remove_if(m_pDevices.begin(), m_pDevices.end(), [](const auto& device)
				{
					return dynamic_cast<T*>(device.get()) != nullptr;
				}), m_pDevices.end());
		}

		template<typename DeviceType, typename BindingType>
		void AddCommand(BindingType binding, std::unique_ptr<BaseCommand> command)
		{
			auto it = std::find_if(m_pDevices.begin(), m_pDevices.end(), [&binding](const auto& device)
				{
					auto* devicePtr = dynamic_cast<DeviceType*>(device.get());
					return devicePtr != nullptr && device->GetIndex() == binding.index; 
				});

			if (it != m_pDevices.end())
			{
				auto* devicePtr = dynamic_cast<DeviceType*>(it->get());
				
				if (devicePtr )
				{
					devicePtr->AddCommand(binding, std::move(command)); 

				}
				else
				{
					std::
						cerr << "Error: Device type mismatch!" << std::endl;
				}
			}
			else
			{
				std::cerr << "Error: Device not found!" << std::endl;
			}
		}
	
		template<typename DeviceType, typename BindingType>
		void RemoveCommand(BindingType binding)
		{
			auto it = std::find_if(m_pDevices.begin(), m_pDevices.end(), [](const auto& device)
				{
					return dynamic_cast<DeviceType*>(device.get()) != nullptr;
				});

			if (it != m_pDevices.end())
			{
				auto* devicePtr = dynamic_cast<DeviceType*>(it->get());
				if (devicePtr)
				{
					devicePtr->RemoveCommand(binding);

				}
				else
				{
					std::
						cerr << "Error: Device type mismatch!" << std::endl;
				}
			}
			else
			{
				std::cerr << "Error: Device not found!" << std::endl;
			}
		}
		bool ProcessInput();

		void CleanUp()
		{
			m_pDevices.clear();
		}
	private:

		InputManager() = default;
		friend class Singleton<InputManager>;

		std::vector<std::unique_ptr<BaseInputDevice>> m_pDevices;
	};
}