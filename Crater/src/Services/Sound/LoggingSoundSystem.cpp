#include "CraterPCH.h"
#include "LoggingSoundSystem.h"
#include <iostream>

namespace CraterEngine
{
	LoggingSoundSystem::LoggingSoundSystem(SoundSystem* pSoundSystem)
		: m_pSoundSystem{pSoundSystem}
	{
	}
	LoggingSoundSystem::~LoggingSoundSystem()
	{
		if ( m_pSoundSystem != nullptr )
		{
			delete m_pSoundSystem;
			m_pSoundSystem = nullptr;
		}
	}
	size_t LoggingSoundSystem::AddAudio(const std::string& filePath)
	{
		std::cout << "Atempting to add audio: " << filePath << std::endl;
			return m_pSoundSystem->AddAudio(filePath);
	};
	void LoggingSoundSystem::Play(const size_t id, const float volume)
	{
		std::cout << "Adding play audio to queue, ID: " << id << ", volume: " << volume << std::endl;
		m_pSoundSystem->Play(id, volume);
	}
	void LoggingSoundSystem::Play(const std::string& filePath, const float volume)
	{
		std::cout << "Adding play audio to queue, Audio File Path: " << filePath << ", volume: " << volume << std::endl;
		m_pSoundSystem->Play(filePath, volume);
	}
	void LoggingSoundSystem::ToggleMuted()
	{
		std::cout << "Toggle Mute" << std::endl;
		m_pSoundSystem->ToggleMuted();
	}
	void LoggingSoundSystem::Pause()
	{
		std::cout << "Pausing" << std::endl;
		m_pSoundSystem->Pause();
	}
	void LoggingSoundSystem::UnPause()
	{
		std::cout << "UnPausing" << std::endl;
		m_pSoundSystem->UnPause();
	}
}