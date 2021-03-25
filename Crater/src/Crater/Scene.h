#pragma once
#include "Crater/Managers/SceneManager.h"

namespace CraterEngine
{	
	class Observer;
	class Subject;
	class GameObject;
	class Scene
	{
	public:
		void Add(GameObject* object);
		void AddObserver(Observer* observer);

		void Update(const float dt);
		void Render() const;
		void Initialize();
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		friend Scene& SceneManager::CreateScene(const std::string& name);
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector<GameObject*> m_Objects{};
		Subject* m_pSubject = nullptr;

		static unsigned int m_IdCounter;
	};
}