#pragma once
#include "SoundSystem.h"
#include <mutex>
#include <thread>
#include <condition_variable>
#include <utility>
#include <queue>
#include <vector>
#include <unordered_map>
#include "src/audio.h"

namespace CraterEngine
{
	class SimpleSDL2AudioMaster : public SoundSystem
	{
	public:
		SimpleSDL2AudioMaster();
		virtual ~SimpleSDL2AudioMaster() override;

		#pragma region deleted
		SimpleSDL2AudioMaster(const SimpleSDL2AudioMaster& other) = delete;
		SimpleSDL2AudioMaster(SimpleSDL2AudioMaster&& other) noexcept = delete;
		SimpleSDL2AudioMaster& operator=(const SimpleSDL2AudioMaster& other) = delete;
		SimpleSDL2AudioMaster& operator=(SimpleSDL2AudioMaster&& other) noexcept = delete;
		#pragma endregion

		virtual void ToggleMuted() override;

		virtual void Pause() override;
		virtual void UnPause() override;

		virtual size_t AddAudio(const std::string& filePath) override;
		virtual void Play(const std::string& filePath, const float volume) override;
		virtual void Play(const size_t id, const float volume) override;
	private:
		void ProcessQueue();
		bool m_IsMuted;
		std::mutex m_Mutex;
		std::thread m_Thread;
		std::condition_variable m_Action;
		std::queue<std::pair<size_t, float>> m_Queue;
		std::unordered_map<size_t, Audio*> m_Sounds;
	};
}

