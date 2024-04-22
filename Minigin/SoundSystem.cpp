#include "SoundSystem.h"

#include <vector>
#include <thread>
#include <iostream>
#include <mutex>
#include "Helpers.h"
#include <unordered_map>
#include "RingBuffer.h"

#include <SDL.h>
#include <SDL_mixer.h>

namespace GameEngine
{
	class SoundSystem::SoundSystemImpl
	{
	public:
		SoundSystemImpl() :
			m_SoundQueue{},
			m_pSoundEffects{},
			m_ActiveAudio{ static_cast<size_t>(MIX_CHANNELS), nullptr }
		{};
		void Load(const std::string& filePath, sound_id id)
		{

			Mix_Chunk* soundEffect = Mix_LoadWAV(filePath.c_str());
			if (soundEffect == nullptr)
			{
				std::cerr << "Couldn't load sound: " << Mix_GetError() << std::endl;
				return;
			}

			std::lock_guard<std::mutex> lock(m_SoundEffectsMutex);

			m_pSoundEffects.insert({ id, std::shared_ptr<Mix_Chunk>(soundEffect, Mix_FreeChunk) });
		}
		void Update()
		{
			// Lock the mutex to synchronize access to m_SoundQueue
			std::lock_guard<std::mutex> lock(m_SoundEffectsMutex);

			// Exit early if queue is empty
			if (m_SoundQueue.GetPending() == 0)
				return;

			// Execute the sound playing logic in a separate thread
			std::thread soundThread([this]() {
				// Lock the mutex again in the worker thread to synchronize access
				std::lock_guard<std::mutex> lock(m_SoundEffectsMutex);

				Sound sound = m_SoundQueue.GetFront();
				std::shared_ptr<Mix_Chunk> pChunk = nullptr;

				if (sound.id != UINT_MAX)
				{
					auto iter = std::find_if(m_pSoundEffects.begin(), m_pSoundEffects.end(),
						[&sound](auto& pair) { return pair.first == sound.id; });

					if (iter != m_pSoundEffects.end())
						pChunk = iter->second;
				}
				if (!pChunk)
				{
					std::cerr << "Failed to load audio chunk for sound ID: " << sound.id << std::endl;
					return;
				}

				// Set volume
				pChunk->volume = static_cast<Uint8>(glm::clamp(sound.volume, 0.f, 1.f) * MIX_MAX_VOLUME);

				// Try playing sound and exit if none are available
				int channel = Mix_PlayChannel(-1, pChunk.get(), 0);
				if (channel == -1)
					return;

				// Keep shared pointer alive while sound is playing
				m_ActiveAudio[channel] = pChunk;

				// Remove front item from queue
				m_SoundQueue.PullFront();
				});

			// Detach the thread to run asynchronously
			soundThread.detach();
		}
		void Play(const sound_id id, const float volume)
		{
			m_SoundQueue.PushBack({ id, volume });
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
			for (auto pSound : m_pSoundEffects)
			{
				Mix_FreeChunk(pSound.second.get());
			}

			Mix_CloseAudio();
			Mix_Quit();
			SDL_Quit();
		}
		~SoundSystemImpl() = default;
	private:
		RingBuffer<Sound, 16> m_SoundQueue;
		std::unordered_map<sound_id, std::shared_ptr<Mix_Chunk>> m_pSoundEffects;
		std::vector<std::shared_ptr<Mix_Chunk>> m_ActiveAudio;
		std::mutex m_SoundEffectsMutex;
	};

	SoundSystem::SoundSystem() :
		m_pImpl(nullptr)
	{
		m_pImpl = std::make_unique<SoundSystemImpl>();

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
		m_pImpl->CleanUp();
	}

	void SoundSystem::Play(const sound_id id, const float volume)
	{
		m_pImpl->Play(id, volume);
	}

	void SoundSystem::Pause()
	{
		m_pImpl->Pause();
	}

	void SoundSystem::Resume()
	{
		m_pImpl->Resume();
	}

	void SoundSystem::Stop()
	{
		m_pImpl->Stop();
	}

	void SoundSystem::Load(const std::string& filePath, const sound_id id)
	{
		m_pImpl->Load(filePath, id);
	}
	void SoundSystem::Update()
	{
		m_pImpl->Update();
	}
}
