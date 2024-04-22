#pragma once
#include "BaseSoundSystem.h"

namespace GameEngine
{
	class NullSoundSystem final : public BaseSoundSystem
	{
	public:
		NullSoundSystem() = default;
		~NullSoundSystem() = default;
		NullSoundSystem(const NullSoundSystem& other) = delete;
		NullSoundSystem(NullSoundSystem&& other) = delete;
		NullSoundSystem& operator=(const NullSoundSystem& other) = delete;
		NullSoundSystem& operator=(NullSoundSystem&& other) = delete;

	private:
		virtual void Play(const sound_id, const float) override {};
		virtual void Pause() override {};
		virtual void Resume() override {};
		virtual void Stop() override {};
		virtual void Load(const std::string&) override {};

	};

}

