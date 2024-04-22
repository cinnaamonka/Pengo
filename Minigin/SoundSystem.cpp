#include "SoundSystem.h"

#include <vector>
#include <thread>
#include <iostream>
#include <mutex>

#include <SDL.h>
#include <SDL_mixer.h>

namespace GameEngine
{
	class SoundSystem::SoundSystemImpl
	{
	public:
		SoundSystemImpl() :m_pSoundEffects{} {};
		virtual ~SoundSystemImpl() = default;

		void Load(const std::string& filePath)
		{
			std::jthread soundThread ([this, filePath](){

					Mix_Chunk* soundEffect = Mix_LoadWAV(filePath.c_str());
					if (soundEffect == nullptr)
					{
						std::cerr << "Couldn't load sound: " << Mix_GetError() << std::endl;
						return;
					}

					std::lock_guard<std::mutex> lock(m_SoundEffectsMutex);

					m_pSoundEffects.push_back(soundEffect);
				}
			);
		}

		void Play(const sound_id id, const float volume)
		{
			std::jthread soundThread
			([this, id, volume]()
				{
					std::lock_guard<std::mutex> lock(m_SoundEffectsMutex);
					if (id >= m_pSoundEffects.size())
					{
						std::cerr << "Sound ID out of range: " << id << std::endl;
						return;
					}

					Mix_Chunk* soundEffect{ m_pSoundEffects[id] };

					if (soundEffect == nullptr)
					{
						std::cerr << "Invalid sound ID: " << id << std::endl;
						return;
					}

					int channel = Mix_PlayChannel(-1, soundEffect, 0);
					if (channel == -1)
					{
						std::cerr << "Failed to play sound: " << Mix_GetError() << std::endl;
						return;
					}

					Mix_Volume(channel, static_cast<int>(volume * MIX_MAX_VOLUME));
				}
			);
		}

		void Pause()
		{
			Mix_Pause(-1);
		}

		void Resume()
		{
			Mix_Resume(-1);
		}

		void Stop()
		{
			Mix_HaltChannel(-1);
		}

		void CleanUp()
		{
			for (Mix_Chunk* pSound : m_pSoundEffects)
			{
				Mix_FreeChunk(pSound);
			}

			Mix_CloseAudio();
			Mix_Quit();
			SDL_Quit();
		}

	private:
		std::vector<Mix_Chunk*> m_pSoundEffects;
		std::mutex m_SoundEffectsMutex;
	};

	SoundSystem::SoundSystem():
		pImpl(nullptr)
	{
		pImpl = new SoundSystemImpl();

		if (Mix_Init(SDL_INIT_AUDIO) < 0)
		{
			std::cerr << "Failed to initialize Sound System: " << SDL_GetError() << std::endl;
			return;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		{
			std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
			return;
		}
	}

	SoundSystem::~SoundSystem()
	{
		pImpl->CleanUp();
		delete pImpl;
	}

	void SoundSystem::Play(const sound_id id, const float volume)
	{
		pImpl->Play(id, volume);
	}

	void SoundSystem::Pause()
	{
		pImpl->Pause();
	}

	void SoundSystem::Resume()
	{
		pImpl->Resume();
	}

	void SoundSystem::Stop()
	{
		pImpl->Stop();
	}

	void SoundSystem::Load(const std::string& filePath)
	{
		pImpl->Load(filePath);
	}
}
