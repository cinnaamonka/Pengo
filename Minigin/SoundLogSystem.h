#pragma once
#include "BaseSoundSystem.h"
#include <memory>

namespace GameEngine
{
	class SoundLogSystem final : public BaseSoundSystem
	{
	public:
		SoundLogSystem(std::unique_ptr<BaseSoundSystem>&& soundSystem);
		~SoundLogSystem() = default;

		SoundLogSystem(const SoundLogSystem& other) = delete;
		SoundLogSystem(SoundLogSystem&& other) = delete;
		SoundLogSystem& operator=(const SoundLogSystem& other) = delete;
		SoundLogSystem& operator=(SoundLogSystem&& other) = delete;

		void Play(const sound_id id, const float volume) override;
		void Pause()override;
		void Resume()override;
		void Stop()override;
		void Load(const std::string& filePath, const sound_id id)override;
		bool Contains(const sound_id id) const override;
		bool IsPlaying(const sound_id id) const override;
	private:
		std::unique_ptr<BaseSoundSystem> pSoundSystem;
	};
}


