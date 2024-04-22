#pragma once
#include <string>

namespace GameEngine
{
	using sound_id = unsigned short;

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
			virtual void Stop() = 0;
			virtual void Load(const std::string& filePath) = 0;
	protected:
		BaseSoundSystem() = default;
		
	};
}


