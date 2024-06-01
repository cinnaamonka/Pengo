#pragma once
#include <string>
#include "Helpers.h"

namespace GameEngine
{
	class BaseSoundSystem
	{
		public:
			virtual ~BaseSoundSystem() = default;
			BaseSoundSystem(const BaseSoundSystem& other) = delete;
			BaseSoundSystem(BaseSoundSystem&& other) = delete;
			BaseSoundSystem& operator=(const BaseSoundSystem& other) = delete;
			BaseSoundSystem& operator=(BaseSoundSystem&& other) = delete;

			virtual void Play(const sound_id id, const float volume) = 0;
			virtual void Pause() = 0;
			virtual void Resume() = 0;
			virtual void Stop(const sound_id id) = 0;
			virtual void Load(const std::string& filePath,const sound_id id) = 0;
			virtual bool Contains(const sound_id id) const = 0;
			virtual bool IsPlaying(const sound_id) const = 0;

	protected:
		BaseSoundSystem() = default;
		
	};
}


