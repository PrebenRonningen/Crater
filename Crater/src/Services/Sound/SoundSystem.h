#pragma once
#include <string>
class SoundSystem
{
public:
	virtual ~SoundSystem() = default;

	SoundSystem() = default;
	#pragma region deleted
	SoundSystem(const SoundSystem& other) = delete;
	SoundSystem(SoundSystem&& other) noexcept = delete;
	SoundSystem& operator=(const SoundSystem& other) = delete;
	SoundSystem& operator=(SoundSystem&& other) noexcept = delete;
	#pragma endregion

	virtual size_t AddAudio(const std::string& filePath) = 0;

	virtual void ToggleMuted() = 0;

	virtual void Pause() = 0;
	virtual void UnPause() = 0;
	

	virtual void PlaySound(const size_t id, const float volume) = 0;
	virtual void PlaySound(const std::string& filePath, const float volume) = 0;
	virtual void PlayMusic(const std::string& filePath, const float volume) = 0;
private:
};

