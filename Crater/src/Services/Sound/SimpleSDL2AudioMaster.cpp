#include "CraterPCH.h"
#include "SimpleSDL2AudioMaster.h"


namespace CraterEngine
{
	SimpleSDL2AudioMaster::SimpleSDL2AudioMaster()
		: m_IsMuted{false}
		, m_Queue{}
		, m_Sounds{}
	{
		initAudio();
		m_Thread = std::thread([this](){this->ProcessQueue();});
	}

	SimpleSDL2AudioMaster::~SimpleSDL2AudioMaster()
	{
		//std::lock_guard<std::mutex> lock{ m_Mutex };
		while ( !m_Queue.empty() )
		{
			m_Queue.pop();
		}
		
		m_Action.notify_one();
		m_Thread.join();

		for ( auto [id, audio] : m_Sounds )
		{
			freeAudio(audio);
		}
		m_Sounds.clear();

		endAudio();
	}

	size_t SimpleSDL2AudioMaster::AddAudio(const std::string& filePath)
	{
		size_t id = std::hash<std::string>()( filePath );;
		Audio* audio = createAudio(filePath.c_str(), 2, 50);

		if( m_Sounds.find(id) == m_Sounds.end() )
			m_Sounds[id] = audio;

		return id;
	}

	void SimpleSDL2AudioMaster::Play(const size_t id, const float volume)
	{
		std::lock_guard<std::mutex> lock{m_Mutex};
		if ( m_Sounds.find(id) != m_Sounds.end() )
		{
			m_Queue.push({id, volume});
			m_Action.notify_one();
		}
	}

	void SimpleSDL2AudioMaster::Play(const std::string& filePath, const float volume)
	{
		std::hash<std::string> hash{};
		size_t id = hash(filePath);

		if ( m_Sounds.find(id) != m_Sounds.end() )
		{
			Play(id, volume);
		}
	}

	void SimpleSDL2AudioMaster::ProcessQueue()
	{
		do
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			if ( !m_Queue.empty() )
			{
				std::pair<size_t, float> play = m_Queue.front();
				m_Queue.pop();
				
				if(!m_IsMuted )
					playSoundFromMemory(m_Sounds[play.first], std::clamp(int(play.second), 0, SDL_MIX_MAXVOLUME));
			}

			if ( m_Queue.empty() )
			{
				m_Action.wait(lock);
			}

		}while(!m_Queue.empty());
	}

	void SimpleSDL2AudioMaster::ToggleMuted()
	{
		m_IsMuted = !m_IsMuted;
		(m_IsMuted ) ? Pause() : UnPause();
	}

	void SimpleSDL2AudioMaster::Pause()
	{
		pauseAudio();
	}

	void SimpleSDL2AudioMaster::UnPause()
	{
		unpauseAudio();
	}

}

