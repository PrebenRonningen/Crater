#include "CraterPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "Observer/Observer.h"
#include "Crater/Observer/Subject.h"

namespace CraterEngine
{
	unsigned int Scene::m_IdCounter = 0;

	Scene::Scene(const std::string& name) : m_Name(name)
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

	void Scene::Add(GameObject* object)
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
		for ( auto& object : m_Objects )
		{
			object->Update(dt);
		}
	}

	void Scene::Render() const
	{
		for ( const auto& object : m_Objects )
		{
			object->Render();
		}
	}
	void Scene::Initialize()
	{
		for ( auto& object : m_Objects )
		{
			object->Initialize();
		}
	}
}