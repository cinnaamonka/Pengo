#include "SoundServiceLocator.h"
#include "NullSoundSystem.h"

namespace GameEngine
{

	std::unique_ptr<BaseSoundSystem> SoundServiceLocator::m_pInstance = nullptr;

	BaseSoundSystem& GameEngine::SoundServiceLocator::GetSoundSystemInstance()
	{
		return *m_pInstance;
	}

	void SoundServiceLocator::RegisterSoundSystem(std::unique_ptr<BaseSoundSystem>&& pSoundSystem)
	{
		if (!pSoundSystem) 
		{
			m_pInstance = std::make_unique<NullSoundSystem>(); 
		}
		else
		{
			m_pInstance = std::move(pSoundSystem);
		}
	}

}
