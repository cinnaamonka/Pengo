#pragma once
#include <memory>
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
		void Load(const std::string& filePath, const sound_id id)override;
		bool Contains(const sound_id id) const override;
		bool IsPlaying(const sound_id id) const override;
	private:
		class SoundSystemImpl;
		std::unique_ptr<SoundSystemImpl> m_pImpl;
	};

}

