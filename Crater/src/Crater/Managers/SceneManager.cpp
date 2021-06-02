#include "CraterPCH.h"
#include "SceneManager.h"
#include "Crater/Scenes/Scene.h"

namespace CraterEngine
{
	SceneManager::SceneManager()
	: m_pActiveScene{ nullptr }
	{

	}
	
	SceneManager::~SceneManager()
	{
		m_pActiveScene = nullptr;
	}

	void SceneManager::Update(const float dt)
	{
		//for ( auto& scene : m_Scenes )
		//{
			m_pActiveScene->Update(dt);
		//}
	}

	void SceneManager::Render()
	{
		//for ( const auto& scene : m_Scenes )
		//{
			m_pActiveScene->Render();
		//}
	}

	void SceneManager::SetActive(const std::string& name)
	{
		if ( !m_Scenes.empty() )
		{
			auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(), [name](Scene* s){return s->GetName() == name;});

			if ( it != m_Scenes.end() )
			{
				m_pActiveScene = *it;
			}
		}
	}

	void SceneManager::SetActive(const Scene* pScene)
	{
		if ( !m_Scenes.empty() )
		{
			auto it = std::find(m_Scenes.begin(), m_Scenes.end(), pScene);

			if ( it != m_Scenes.end() )
			{
				m_pActiveScene = *it;
			}
		}
	}

	//void SceneManager::AddScene(Scene* pScene)
	//{
	//	if(m_pActiveScene == nullptr )
	//		m_pActiveScene = pScene;
	//
	//	m_Scenes.push_back(pScene);
	//}


	//void SceneManager::NextScene()
	//{
	//	if ( !m_Scenes.empty() )
	//	{
	//		auto it = std::find(m_Scenes.begin(), m_Scenes.end(), m_pActiveScene);

	//		if ( it != m_Scenes.end() )
	//		{
	//			++it;
	//			m_pActiveScene = ( it == m_Scenes.end() ) ? m_Scenes[0] : *it;
	//		}
	//	}
	//}

	//Scene* SceneManager::GetActiveScene() const
	//{
	//	return m_pActiveScene;
	//}

	void SceneManager::Destroy()
	{
		for ( auto& scene : m_Scenes )
		{
			delete scene;
			scene = nullptr;
		}
	}
}