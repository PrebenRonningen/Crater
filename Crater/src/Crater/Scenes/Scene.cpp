#include "CraterPCH.h"
#include "Scene.h"
#include "../GameObject.h"
#include "../Observer/Observer.h"
#include "Crater/Observer/Subject.h"
#include "Crater/Components/RenderableComponent.h"
namespace CraterEngine
{
	Scene::Scene(const std::string& name)
	: m_Name(name)
	{
		m_pSubject = new Subject();
	}

	Scene::~Scene()
	{
		for ( GameObject* obj : m_Objects )
		{
			delete obj;
			obj = nullptr;
		}
		m_Objects.clear();

		if ( m_pSubject )
		{
			delete m_pSubject;
			m_pSubject = nullptr;
		}
	}

	void Scene::AddGameObject(GameObject* object)
	{
		object->SetSubject(m_pSubject);
		m_Objects.push_back(object);
	}

	void Scene::AddObserver(Observer* observer)
	{
		m_pSubject->AddObserver(observer);
	}
	void Scene::Update(const float dt)
	{
		for ( auto pO : m_Objects )
		{
			pO->Update(dt);
		}
	}
	void Scene::Render() const
	{
		for ( auto pO : m_RenderObjects )
		{
			pO->Render();
		}
	}
	void Scene::RegisterComponentToRender(Component* pComponent)
	{
		m_RenderObjects.push_back(pComponent);
	}
}