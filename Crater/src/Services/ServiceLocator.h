#pragma once

class SoundSystem;
class NullSoundSystem;

class ServiceLocator final
{
public:
	~ServiceLocator() = default;
	static SoundSystem& GetSoundService();

	static void Destroy();

	static void RegisterSoundSystem(SoundSystem* soundSystem );
private:
	ServiceLocator() = default;

	static NullSoundSystem m_NullSoundServiceInstance;
	static SoundSystem* m_SoundServiceInstance;
};
