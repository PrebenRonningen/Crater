#include "CraterPCH.h"
#include "SceneManager.h"
#include "Crater/Scene.h"

namespace CraterEngine
{
	void SceneManager::Update(const float dt)
	{
		for ( auto& scene : m_Scenes )
		{
			scene->Update(dt);
		}
	}

	void SceneManager::Render()
	{
		for ( const auto& scene : m_Scenes )
		{
			scene->Render();
		}
	}

	Scene& SceneManager::CreateScene(const std::string& name)
	{
		Scene* scene = new Scene(name);
		m_Scenes.push_back(scene);
		return *scene;
	}
	void SceneManager::Destroy()
	{
		for ( auto& scene : m_Scenes )
		{
			delete scene;
			scene = nullptr;
		}
	}
}