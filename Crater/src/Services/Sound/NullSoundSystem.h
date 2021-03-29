#pragma once
#include "SoundSystem.h"
class NullSoundSystem final : public SoundSystem
{
public:
	virtual ~NullSoundSystem() override {};

	NullSoundSystem() = default;
	#pragma region deleted
	NullSoundSystem(const NullSoundSystem& other) = delete;
	NullSoundSystem(NullSoundSystem&& other) noexcept = delete;
	NullSoundSystem& operator=(const NullSoundSystem& other) = delete;
	NullSoundSystem& operator=(NullSoundSystem&& other) noexcept = delete;
	#pragma endregion

	virtual void ToggleMuted() override{};

	virtual void Pause() override{};
	virtual void UnPause() override{};

	virtual size_t AddAudio(const std::string& ) override{return size_t(-1);};
	virtual void PlaySound(const size_t, const float) override{};
	virtual void PlaySound(const std::string&, const float) override{};
	virtual void PlayMusic(const std::string& , const float ){};
};