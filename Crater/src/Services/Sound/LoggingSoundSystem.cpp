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
		std::cout << "Atempting to add sound: " << filePath << std::endl;
			return m_pSoundSystem->AddAudio(filePath);
	};
	void LoggingSoundSystem::PlaySound(const size_t id, const float volume)
	{
		std::cout << "Adding play sound to queue, ID: " << id << ", volume: " << volume << std::endl;
		m_pSoundSystem->PlaySound(id, volume);
	}
	void LoggingSoundSystem::PlaySound(const std::string& filePath, const float volume)
	{
		std::cout << "Adding play sound to queue, Audio File Path: " << filePath << ", volume: " << volume << std::endl;
		m_pSoundSystem->PlaySound(filePath, volume);
	}
	void LoggingSoundSystem::PlayMusic(const std::string& filePath, const float volume)
	{
		std::cout << "Adding play music to queue, Audio File Path: " << filePath << ", volume: " << volume << std::endl;
		m_pSoundSystem->PlayMusic(filePath, volume);
	}
	void LoggingSoundSystem::ToggleMuted()
	{
		std::cout << "Toggle Mute Sounds" << std::endl;
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