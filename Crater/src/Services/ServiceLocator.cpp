#include "CraterPCH.h"
#include "ServiceLocator.h"
#include "Sound/SoundSystem.h"
#include "Sound/NullSoundSystem.h"

NullSoundSystem ServiceLocator::m_NullSoundServiceInstance{};
SoundSystem* ServiceLocator::m_SoundServiceInstance = &ServiceLocator::m_NullSoundServiceInstance;
//LogSystem* ServiceLocator::m_LogServiceInstance{};

SoundSystem& ServiceLocator::GetSoundService()
{
	return *m_SoundServiceInstance;
}

void ServiceLocator::Destroy()
{
	if ( m_SoundServiceInstance != nullptr && m_SoundServiceInstance != &m_NullSoundServiceInstance )
	{
		delete m_SoundServiceInstance;
		m_SoundServiceInstance = nullptr;
	}
}

void ServiceLocator::RegisterSoundSystem(SoundSystem* pSoundSystem)
{
	m_SoundServiceInstance = ( pSoundSystem == nullptr ) ? &m_NullSoundServiceInstance : pSoundSystem;
}
