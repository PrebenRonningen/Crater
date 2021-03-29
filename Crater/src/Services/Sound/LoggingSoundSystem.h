#pragma once
#include "SoundSystem.h"

namespace CraterEngine
{
	class LoggingSoundSystem : public SoundSystem
	{
	public:
		LoggingSoundSystem(SoundSystem* pSoundSystem);
		virtual ~LoggingSoundSystem() override;

		#pragma region deleted
		LoggingSoundSystem(const LoggingSoundSystem& other) = delete;
		LoggingSoundSystem(LoggingSoundSystem&& other) noexcept = delete;
		LoggingSoundSystem& operator=(const LoggingSoundSystem& other) = delete;
		LoggingSoundSystem& operator=(LoggingSoundSystem&& other) noexcept = delete;
		#pragma endregion

		virtual void ToggleMuted() override;

		virtual void Pause() override;
		virtual void UnPause() override;

		virtual size_t AddAudio(const std::string& filePath) override;
		virtual void PlaySound(const size_t id, const float volume) override;
		virtual void PlaySound(const std::string& filePath, const float volume) override;
		virtual void PlayMusic(const std::string& filePath, const float volume);

	private:
		SoundSystem* m_pSoundSystem;
	};
}

