#pragma once
#include "Crater/Managers/SceneManager.h"
#include "Crater/Components/RenderableComponent.h"

namespace CraterEngine
{	
	class GameObject;
	class Subject;
	class Observer;
	class Scene
	{
	public:
		virtual ~Scene();

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
		const std::string& GetName() const{ return m_Name; }

		void Add(GameObject* object);
		void AddObserver(Observer* observer);

		virtual void Update(const float dt) = 0;
		virtual void Render() const = 0;
		virtual void Initialize() = 0;
	protected:
		std::string m_Name;
		std::vector<GameObject*> m_Objects{};
		std::vector<GameObject*> m_RenderObjects{};

		Subject* m_pSubject = nullptr;

		explicit Scene(const std::string& name);

	};
}