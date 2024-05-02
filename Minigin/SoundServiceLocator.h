#pragma once
#include <memory>
#include "Singleton.h"
#include "BaseSoundSystem.h"

namespace GameEngine
{
	class BaseSoundSystem;

	class SoundServiceLocator final : public Singleton<SoundServiceLocator>
	{
	public:
		
		SoundServiceLocator() = default;
		~SoundServiceLocator() = default;

		SoundServiceLocator(const SoundServiceLocator& other) = delete;
		SoundServiceLocator(SoundServiceLocator&& other) = delete;
		SoundServiceLocator& operator=(const SoundServiceLocator& other) = delete;
		SoundServiceLocator& operator=(SoundServiceLocator&& other) = delete;

		static BaseSoundSystem& GetSoundSystemInstance();
		static void RegisterSoundSystem(std::unique_ptr<BaseSoundSystem>&& pSoundSystem);

	private:
		static std::unique_ptr<BaseSoundSystem> m_pInstance;

	};
}


