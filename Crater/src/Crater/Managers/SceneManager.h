#pragma once
#include "Singleton.h"
#include <vector>
//
//#include "Crater/Scenes/Scene.h"

namespace CraterEngine
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		template <typename T>
		T& CreateScene(const std::string& name)
		{
			T* scene = new T{name};
			m_Scenes.push_back(scene);
			if(m_pActiveScene == nullptr )
				m_pActiveScene = scene;
			return *scene;
		}
		
		void Destroy();
		void Update(const float dt);
		void Render();
		void SetActive(const std::string& name);
		void SetActive(const Scene* pScene);

		virtual ~SceneManager() override;
	private:
		friend class Singleton<SceneManager>;
		SceneManager();
		Scene* m_pActiveScene = nullptr;
		std::vector<Scene*> m_Scenes;
	};
}