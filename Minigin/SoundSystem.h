#pragma once
#include "BaseSoundSystem.h"

namespace GameEngine
{
	class SoundSystem final : public BaseSoundSystem
	{
	public:
		SoundSystem();
		~SoundSystem();
		void Play(const sound_id id, const float volume) override;
		void Pause()override;
		void Resume()override;
		void Stop()override;
		void Load(const std::string& filePath)override;
	private:
		class SoundSystemImpl;
		SoundSystemImpl* pImpl;
	};

}

